#include <iostream>
#include <unistd.h>
#include <getopt.h>
using namespace std;

int main(int argc, char **argv)
{
    int opt;
    int digit_optind = 0;
    int option_index = 0;
    char *optstring = "a:b:c:d";

    static struct option long_options[] = {
        { "reqarg", required_argument, NULL, 'r'},
        { "noarg", no_argument, NULL, 'n'},
        { "optarg", optional_argument, NULL, 'o'},
        { 0, 0, 0, 0}
    };

    while((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
    {
        cout << "opt = " << opt << endl;
        cout << "optarg = " << optarg << endl;
        cout << "optind = " << optind << endl;
        cout << "argv[optind -1] = " << argv[optind - 1] << endl;
        cout << "option_index = " << option_index << endl;
    }
    return 0;

    return 0;
}
