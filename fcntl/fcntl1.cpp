#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char **argv)
{
    pid_t pid;
    int fd = open("text.txt", O_TRUNC| O_RDWR| O_APPEND | O_CREAT, 0777);
    if(fd < 0)
    {
        cout << "open error " << endl;
        exit(-1);
    }

    cout << "fd = " << fd << endl;
    fcntl(fd, F_SETFD, 0);
    write(fd, "ADD TEST \n", 20);
    pid = fork();
    if(pid < 0)
    {
        cout << "fork error " << endl;
        exit(-1);
    }
    if(pid == 0)
    {
        cout << "fd = " << fd << endl;
        //int ret = excel("./main", "./main", (char *) &fd, NULL);
        if(ret < 0)
        {
            cout << "excel error" << endl;
            exit(-1);
        }
        exit(0);
    }

    wait(NULL);
    write(fd, "hello c++ program!\n", strlen("hello c++ program!\n"));

    close(fd);

    return 0;
}

