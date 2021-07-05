#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

bool daemonize()
{
    pid_t pid = fork();
    if (pid < 0) {
        return false;
    }
    else if (pid > 0) {
        exit(0);
    }

    umask(0);

    //设置新的会话，设置本进程为进程组的首领
    pid_t sid = setsid();
    if (sid < 0)
        return false;

    //切换工作目录
    if ((chdir("/")) < 0)
        return false;

    printf("2. pid: %ld, parent id: %ld\n", (long)getpid(), (long)getppid());

    //关闭标准输入，标准输出，标准错误输出
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //重定向标准输入，标准输出，标准错误输出到/dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);


    return true;
}

int main(int argc, char **argv)
{
    printf("1. pid: %ld, parent id: %ld\n", (long) getpid(), (long) getppid());;
    daemonize();


    return 0;
}