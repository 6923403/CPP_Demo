#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void signalHandler(int signum)
{
    cout << "signum : " << signum << endl;

    exit(signum);
}

int main(int argc, char **argv)
{
    int i = 0;
    signal(SIGINT, signalHandler);

    while(++i)
    {
        cout << "Going to sleep " << endl;
        if(i == 3)
        {
            raise(SIGINT);
        }
        sleep(1);
    }
}
