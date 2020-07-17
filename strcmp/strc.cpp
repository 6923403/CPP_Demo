#include <iostream>
#include <cstring>
using namespace std;

void test1(int argc, char **argv)
{
    /*
     * 如果返回值小于 0，则表示 str1 小于 str2。
     * 如果返回值大于 0，则表示 str1 大于 str2。
     * 如果返回值等于 0，则表示 str1 等于 str2。
     */
    for(int i = 1; i < argc; ++i)
    {
        string arg(argv[i]);
        if(arg == "-h" || arg == "--help") 
        {
            cout << "-h, -s, -n" << endl;
            return;
        }
        else if(strcmp(argv[i], "-s") == 0)
        {
            cout << "-ssss" << endl;
        }
        else if(strcmp(argv[i], "-n") == 0)
        {
            cout << "-nnnnn" << endl;
        }
        else
        {
            cout << "Nullll " << endl;
        }
    }
}

int main(int argc, char **argv)
{
    test1(argc, argv);

    return 0;
}
