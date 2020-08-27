#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

bool start_daemon()
{
    int fd;

    switch(fork()) //-1
    {
        case -1:
            printf("fork() failed \n");
            return false;
        case 0:
            break;
        default:
            exit(0);
    }

    /*
    pid_t setsid(void);
    进程调用setsid()可建立一个新对话期间。
    如果调用此函数的进程不是一个进程组的组长，则此函数创建一个新对话期，结果为：
        1、此进程变成该新对话期的对话期首进程（session leader，对话期首进程是创建该对话期的进程）。
           此进程是该新对话期中的唯一进程。
        2、此进程成为一个新进程组的组长进程。新进程组ID就是调用进程的进程ID。
        3、此进程没有控制终端。如果在调用setsid之前次进程有一个控制终端，那么这种联系也被解除。
    如果调用进程已经是一个进程组的组长，则此函数返回错误。为了保证不处于这种情况，通常先调用fork()，
    然后使其父进程终止，而子进程继续执行。因为子进程继承了父进程的进程组ID，而子进程的进程ID则是新
    分配的，两者不可能相等，所以这就保证了子进程不是一个进程组的组长。
    */
    if(setsid() == -1) //2
    {
        printf("setsid() failed \n");
        return false;
    }

    switch(fork())
    {
        case -1:
            printf("fork() failed \n");
            return false;
        case 0:
            break;
        default:
            exit(0);
    }

    umask(0); //3
    chdir("/"); //4

    long maxfd;
    if((maxfd = sysconf(_SC_OPEN_MAX)) != -1)
    {
        for(fd = 0; fd < maxfd; fd++)
        {
            close(fd);
        }
    }

    fd = open("/dev/null", O_RDWR);
    if(fd == -1)
    {
        printf("open(\"/dev/null\") failed \n");
        return false;
    }

    /*
    // Standard file descriptors.
    #define STDIN_FILENO    0   // Standard input.
    #define STDOUT_FILENO   1   // Standard output.
    #define STDERR_FILENO   2   // Standard error output.
    */

    /*
    int dup2(int oldfd, int newfd);
    dup2()用来复制参数oldfd所指的文件描述符，并将它拷贝至参数newfd后一块返回。
    如果newfd已经打开，则先将其关闭。
    如果oldfd为非法描述符，dup2()返回错误，并且newfd不会被关闭。
    如果oldfd为合法描述符，并且newfd与oldfd相等，则dup2()不做任何事，直接返回newfd。
    */
    if(dup2(fd, STDIN_FILENO) == -1)
    {
        printf("dup2(STDIN) failed \n");
        return false;
    }

    if(dup2(fd, STDOUT_FILENO) == -1) 
    {
        printf("dup2(STDOUT) failed\n");
        return false;
    }

    if(dup2(fd, STDERR_FILENO) == -1) 
    {
        printf("dup2(STDERR) failed\n");
        return false;
    }

    if (fd > STDERR_FILENO) 
    {
        if (close(fd) == -1) {
            printf("close() failed\n");
            return false;
        }
    }

    return true;
}

int main(int argc, char **argv)
{
    start_daemon();

    while(true)
    {
        sleep(1000);
    }

    return 0;
}
