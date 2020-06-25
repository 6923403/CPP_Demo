#include <csignal>
#include <iostream>
#include <unistd.h>
using namespace std;

void signum(int num)
{
    cout << "Signal: " << num << endl;

    exit(num);
}

int main(int argc, char **argv)
{
    signal(SIGINT, signum);

    int i;
    while(true)
    {
        cout << "Go To Sleep..." << endl;
        i++;

        if(i == 10)
        {
            raise(SIGINT); //raise reSIGINT
        }
        sleep(1);
    }

    return 0;
}
