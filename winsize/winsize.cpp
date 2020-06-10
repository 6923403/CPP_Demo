#include <iostream>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

int main(int argc, char **argv)
{
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);

    std::cout << "ws_col = " << w.ws_col << std::endl;
    std::cout << "ws_row = " << w.ws_row << std::endl;

    return 0;
}

