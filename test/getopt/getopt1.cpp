#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int opt;
    char *optstring = "a:b:c:d";

    while((opt = getopt(argc, argv, optstring)) != -1)
    {
        cout << "opt = " << opt << endl;
        cout << "optarg = " << optarg << endl;
        cout << "optind = " << optind << endl;
        cout << "argv[optind - 1] = " << argv[optind - 1] << endl;
    }

    return 0;
}
