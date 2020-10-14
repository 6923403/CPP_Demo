#include <iostream>
#include <unistd.h>
#include <cassert>
#include <cstdlib>
#include <errno.h>
#include <cstring>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 4096

enum CHECK_STATE
{
    CHECK_STATE_REQUESTLINE = 0,
    CHECK_STATE_HEADER
};

enum LINE_STATUS
{
    LINE_OK = 0,
    LINE_BAD,
    LINE_OPEN
};

enum HTTP_CODE
{
    NO_REQUEST,
    GET_REQUEST,
    BAD_REQUEST,
    FORBIDDEN_REQUEST,
    INTERNAL_ERROR,
    CLOSED_CONNECTION
};

static const char * szret[] = {"I get a correct result \n", "Something wrong \n"};

LINE_STATUS parse_line(char * buffer, int & checked_index, int & read_index)
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
            else if(buffer[checked_index + 1] == '\n')
            {
                buffer[checked_index++] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;
            }

            return LINE_BAD;
        }
        else if(temp == '\n')
        {
            if((checked_index > 1) && buffer[checked_index = 1] == '\r')
            {
                buffer[checked_index - 1] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }

    return LINE_OPEN;
}

HTTP_CODE parse_requestline(char * temp, CHECK_STATE & checkstate)
{
    char * url = strpbrk(temp, " \t");
    if(!url)
    {
        return BAD_REQUEST;
    }
    *url++ = '\0';

    char * method = temp;
    if(strcasecmp(method, "GET") == 0)
    {
        std::cout << "The request methos is GET" << std::endl;
    }
    else
    {
        return BAD_REQUEST;
    }

    url += strspn(url, " \t");
    char * version = strpbrk(url, " \t");
    if(!version)
    {
        return BAD_REQUEST;
    }
    * version++ = '\0';
    * version += strspn(version, " \t");
    if(strcasecmp(version, "HTTP/1.1") != 0)
    {
        return BAD_REQUEST;
    }

    if(strncasecmp(url, "http://", 7) == 0)
    {
        url += 7;
        url = strchr(url, '/');
    }

    if(!url || url[0] != '/')
    {
        return BAD_REQUEST;
    }

    std::cout << "The request URL is: " << url << std::endl;
    checkstate = CHECK_STATE_HEADER;
    return NO_REQUEST;

}

HTTP_CODE parse_headers(char * temp)
{
    if(temp[0] == '\0')
    {
        return GET_REQUEST;
    }
    else if(strncasecmp(temp, "Host:", 5) == 0)
    {
        temp += 5;
        temp += strspn(temp, "\t");
        std::cout << "The request host is: " << temp << std::endl; 
    }
    else
    {
        std::cout << "I can not handle this header" << std::endl;
    }

    return NO_REQUEST;
}

HTTP_CODE parse_content(char * buffer, int & checked_index, 
            CHECK_STATE & checkstate, int & read_index, int & start_line)
{
    LINE_STATUS linestatus = LINE_OK;
    HTTP_CODE retcode = NO_REQUEST;
    while((linestatus = parse_line(buffer, checked_index, read_index)) == LINE_OK)
    {
        char * temp = buffer + start_line;
        start_line = checked_index;
        switch(checkstate)
        {
            case CHECK_STATE_REQUESTLINE:
                retcode = parse_requestline(temp, checkstate);
                if(retcode == BAD_REQUEST)
                {
                    return BAD_REQUEST;
                }
                break;
            case CHECK_STATE_HEADER:
                retcode = parse_headers(temp);
                if(retcode == BAD_REQUEST)
                {
                    return BAD_REQUEST;
                }
                else if(retcode == GET_REQUEST)
                {
                    return GET_REQUEST;
                }
                break;
            default:
                return INTERNAL_ERROR;
        }
    }

    if(linestatus == LINE_OPEN)
    {
        return NO_REQUEST;
    }
    else
    {
        return BAD_REQUEST;
    }
}

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        std::cout << "argc <= 2" << std::endl;
        exit(1);
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);


    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    int ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 20);
    assert(ret != -1);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int fd = accept(listenfd, (struct sockaddr *) &client_addr, &client_addr_len);
    if(fd < 0)
    {
        std::cout << "errno " << errno << std::endl;
    }
    else
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        int data_read = 0;
        int read_index = 0;
        int checked_index = 0;
        int start_line = 0;
        CHECK_STATE checkstate = CHECK_STATE_REQUESTLINE;

        while(true)
        {
            data_read = recv(fd, buffer + read_index, BUFFER_SIZE - read_index, 0);
            if(data_read == -1)
            {
                std::cout << "reading failed" << std::endl;
                break;
            }
            else if(data_read == 0)
            {
                std::cout << "remote client has closed the connection " << std::endl;
                break;
            }
            read_index += data_read;
            HTTP_CODE result = parse_content(buffer, checked_index, 
                                checkstate, read_index, start_line);
            if(result == NO_REQUEST)
            {
                continue;
            }
            else if(result == GET_REQUEST)
            {
                send(fd, szret[0], strlen(szret[0]), 0);
                break;
            }
            else
            {
                send(fd, szret[1], strlen(szret[1]), 0);
                break;
            }
        }
        close(fd);
    }
    close(listenfd);

    return 0;
}
