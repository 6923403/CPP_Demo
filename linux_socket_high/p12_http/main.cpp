#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

const int BUFFER_SIZE = 4096;

//主状态机
enum CHECK_STATE
{
    CHECK_STATE_REQUESTLINE = 0, 	//当前正在分析请求行
    CHECK_STATE_HEADER,				//当前正在分析头部字段
    CHECK_STATE_CONTENT
};

//从状态机，行的读取状态
enum LINE_STATUS
{
    LINE_OK = 0,		//读到完整行
    LINE_BAD,			//行出错
    LINE_OPEN			//行数据不完整
};

//HTTP请求结果
enum HTTP_CODE
{
    NO_REQUEST,			//请求不完整， 需要继续读取客户端数据
    GET_REQUEST,			//获得了完整的客户请求
    BAD_REQUEST,			//客户请求有语法错误
    FORBIDDEN_REQUEST,	//客户对资源没有足够的访问权限
    INTERNAL_ERROR,		//服务器内部错误
    CLOSED_CONNECTION		//客户端已关闭连接
};

//发给客户端的应答报文（简化版）
static const char *szret[] = {"I get a correct result\n",
                              "Something wrong\n"};

LINE_STATUS parse_line(char *buffer, int &checked_index, int &read_index);
HTTP_CODE parse_requestline(char *szTemp, CHECK_STATE &checkstate);
HTTP_CODE parse_headers(char *szTemp);
HTTP_CODE parse_content(char *buffer, int &checked_index, CHECK_STATE &checkstate, int &read_index, int &start_index);

int main(int argc, char **argv)
{
    int port = 20999;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
    addr.sin_port = htons(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd > 0);
    int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    int ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);
    ret = listen(sockfd, 10);
    assert(ret != -1);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int fd = accept(listenfd, (struct sockaddr*) &client_addr, &client_addr_len);
    if(fd < 0)
    {
        std::cout << __LINE__ << "  error" << std::endl;
    }
    else
    {
        char buffer[BUFFER_SIZE];			//读缓冲区
        memset(buffer, '\0', BUFFER_SIZE);

        int data_read = 0;
        int read_index = 0;					//当前已读取的字节数
        int checked_index = 0;				//当前已分析完的字节数
        int start_line = 0;					//buffer中一行的起始位置

        CHECK_STATE checkstate = CHECK_STATE_REQUESTLINE;
        while(true)
        {
            data_read = recv(fd, buffer + read_index, BUFFER_SIZE - read_index, 0);
            if (data_read == -1)
            {
                printf("reading failed\n");
                break;
            }
            else if (data_read == 0)
            {
                printf("remote client has closed the connection\n");
                break;
            }

            //分析已读取的数据
            HTTP_CODE result = parse_content(buffer, checked_index, checkstate, read_index, start_line);

            read_index += data_read;
        }
    }

    return 0;
}
//解析一行内容
LINE_STATUS parse_line(char *buffer, int &checked_index, int &read_index)
{
    char temp;

    for(; checked_index < read_index; ++checked_index)
    {
        temp = buffer[checked_index];
        if(temp == '\r')
        {
            if((checked_index + 1) == read_index)
            {
                return LINE_OPEN;
            }
            else if (buffer[checked_index+1] == '\n')
            {
                buffer[checked_index++] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;
            }

            return LINE_BAD;
        }
        else if(temp == '\n')
        {
            if (checked_index > 1 && buffer[checked_index-1] == '\r') {
                buffer[checked_index-1] = '\0';
                buffer[checked_index++] = '\0';

                return LINE_OK;
            }
            return LINE_BAD;
        }
    }

    return LINE_OPEN;
}

/*分析请求行
 * 模拟如下：
 * GET / HTTP/1.1
 * Host: www.baidu.com
 *
*/
HTTP_CODE parse_requestline(char *szTemp, CHECK_STATE &checkstate)
{
    char *szurl = strpbrk(szTemp, " \t");
    if(!szurl)
    {
        return BAD_REQUEST;
    }

    *szurl++ = '\0';
    char *szMethod = szTemp;

    if(strcasecmp(szMethod, "GET") == 0)
    {
        std::cout << "The request method is GET\\n" << std::endl;
    }

    szurl += strspn(szurl, " \t");

    char *szversion += strspn(szversion, " \t");

    if(strcasecmp(szversion, "HTTP/1.1") != 0)
    {
        return BAD_REQUEST;
    }

    if(strncasecmp(szurl, "http://", 7) == 0)
    {
        szurl += 7;
        szurl = strchr(szurl, '/');
    }

    if(!szurl || szurl[0] != '/')
    {
        return BAD_REQUEST;
    }

    std::cout << "The request URL is: " << szurl << std::endl;

    checkstate = CHECK_STATE_HEADER;

    return NO_REQUEST;
}

//分析头部字段
HTTP_CODE parse_headers(char *szTemp)
{
    if (szTemp[0] == '\0') {
        return GET_REQUEST;		//遇到空行，表示我们得到一个正确的HTTP请求
    }
    else if (strncasecmp(szTemp, "Host:", 5) == 0) {
        szTemp += 5;
        szTemp += strspn(szTemp, " \t");
        printf("the request host is: %s\n", szTemp);
    }
    else {	//其它头部字段不处理
        printf("I can not handle this header\n");
    }

    return NO_REQUEST;
}

//分析HTTP请求
HTTP_CODE parse_content(char *buffer, int &checked_index, CHECK_STATE &checkstate, int &read_index, int &start_index)
{
    LINE_STATUS linestatus = LINE_OK;
    HTTP_CODE retcode = NO_REQUEST;

    while((linestatus = parse_line(buffer, checked_index, read_index)) == LINE_OK)
    {
        char *sztemp = buffer + start_index; //start_line是行的起始位置
        start_index = checked_index;

        switch(checkstate)
        {
            case CHECK_STATE_REQUESTLINE:
            {
                retcode = parse_requestline(sztemp, checkstate);
                if(retcode = BAD_REQUEST)
                {
                    return BAD_REQUEST;
                }

                break;
            }
            case CHECK_STATE_HEADER:
            {
                retcode = parse_headers(sztemp);
                if (retcode == BAD_REQUEST) {
                    return BAD_REQUEST;
                }
                else if(retcode == GET_REQUEST) {
                    return GET_REQUEST;
                }
                break;
            }
            default:
            {
                return INTERNAL_ERROR;
            }
        }

    }
    if (linestatus == LINE_OPEN)		//不完整行，要继续读取客户端数据才能进一步分析
        return NO_REQUEST;
    else
        return BAD_REQUEST;

    return BAD_REQUEST;
}