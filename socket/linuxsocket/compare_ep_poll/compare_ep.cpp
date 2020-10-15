
int ret = poll(fds, MAX_EVENT_NUMBER, -1);
for(int i = 0; i < MAX_EVENT_NUMBER; ++i)
{
    if(fds[i].revents & POLLIN)
    {
        int sockfd = fds[i].fd;
    }
}

int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);

for(int i = 0; i < ret; i++)
{
    int sockfd = events[i].data.fd;
}
