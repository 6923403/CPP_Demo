#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void signalHandler(int signum)
{
    cout << "interrupt signal(" << signum << ")received. \n";

    exit(signum);

}

int main(int argc, char **argv)
{
    signal(SIGINT, signalHandler);

    while(1)
    {
        cout << "Going to sleep " << endl;
        sleep(1);
    }
}

