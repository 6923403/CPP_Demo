#ifndef HTTP_CONN_H
#define HTTP_CONN_H

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>
#include <sys/stat.h>
#include <cstring>
#include <pthread.h>

class  http_conn
{
public:
    static const int FILE_LEN = 1024;
    static const int READ_BUFFER_SIZE = 2048;
    static const int WRITE_BUFFER_SIZE = 1024;
    enum METHOD
    {
        GET = 0,
        POST,
        HEAD,
        PUT,
        DELETE,
        TRACE,
        OPTIONS,
        CONNECT,
        PATCH
    };

    /*
     * 解析客户请求时 主状态机所处的状态
     */
    enum CHECK_STATE
    {
        CHECK_STATE_REQUESTLINE = 0,
        CHECK_STATE_HEADER,
        CHECK_STATE_CONTENT
    };

    /*
     * 服务器处理HTTP请求的可能的结果
     */
    enum HTTP_CODE
    {
        NO_REQUEST,
        GET_REQUEST,
        BAD_REQUEST,
        NO_RESOURCE,
        FORBIDDEN_REQUEST,
        FILE_REQUEST,
        INETRNAL_ERROR,
        CLOSED_CONNECTION
    };

    /*
     * 行的读取状态
     */
    enum LINE_STATUS
    {
        NO_REQUEST,
        GET_REQUEST,
        BAD_REQUEST,
        NO_RESOURCE,
        FORBIDDEN_REQUEST,
        FILE_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION
    };

public:
    http_conn()
    {}

    ~http_conn()
    {}

    void init(int sockfd, const sockaddr_in& addr);
    void close_conn(bool real_close = true);
    void process();
    bool read();
    bool write();

private:
    void init();
    HTTP_CODE process_read();
    bool process_write(HTTP_CODE ret);


    HTTP_CODE parse_request_line(char* text);
    HTTP_CODE parse_headers(char* text);
    HTTP_CODE parse_content(char* text);
    HTTP_CODE do_request();
    char* get_line()
    {
        return m_read_buf + m_start_line;
    }

    LINE_STATUS parse_line();
    void unmap();
    bool add_response(const char* format, ...);
    bool add_content(const char* content);
    bool add_status_line(int status, const char* title);
    bool add_headers(int content_len);
    bool add_content_length(int content_len);
    bool add_linger();
    bool add_blank_line();

public:
    static int m_epollfd;
    static int m_user_count;

private:
    int m_sockfd;
    sockaddr_in m_address;
    char m_read_buf[READ_BUFFER_SIZE];
    char m_write_buf[WRITE_BUFFER_SIZE];

    /*
     * 标识读缓冲中已经读入的客户数据的最后一个字节的下一个位置
     */
    int m_read_idx;

    /*
     *  当前正在分析的字符在读缓冲区中的位置
     */
    int m_checked_idx;

    /*
     * 当前正在解析的行的起始位置
     */
    int m_start_line;

    /*
     * 写缓冲区中待发送的字节数
     */
    int m_write_idx;

    CHECK_STATE m_check_state;
    METHOD m_method;

    /*
     * 请求目标文件完整路径
     */
    char m_real_file[FILE_LEN];
    char* m_url;

    /*
     * HTTP/1.1
     */
    char* m_version;

    char* m_host;
    int m_content_length;

    /*
     * HTTP请求是否要求保持连接
     */
    bool m_linger;

    /*
     * 客户请求的目标文件被mmap到内存中的起始位置
     */
    char* m_file_address;

    /*
     * 目标文件的状态。可以判断文件是否存在、是否为目录、是否可读，并获取文件大小等
     */
    struct stat m_file_stat;

    /*
     * 采用writev来执行写操作，所以定义下面两个成员，其中m_iv_count表示被写内存块的数量*/
     */
     struct iovec m_iv[2];
     int m_iv_count;

};

#endif //HTTP_CONN_H
