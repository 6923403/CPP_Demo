#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <assert.h>
#include <signal.h>

#include "lst_timer.h"

const int FD_LIMIT = 65535;                  //客户端最大连接数
const int MAX_EVENT_NUMBER = 1024;
const int TIMESLOT = 5;                      //定时器的超时时间

static int pipefd[2];
static sort_timer_lst timer_lst;
static int epollfd = 0;

void cb_func(client_data *user_data);   //定时器回调函数

void cb_func(client_data *user_data)
{
    //删除非活动连接上的注册事件，并关闭
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    assert(user_data);
    close(user_data->sockfd);
    std::cout << "close fd: " << user_data->sockfd << std::endl;
}
