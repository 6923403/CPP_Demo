#include <iostream>
#include <unistd.h>
#include <getopt.h>
using namespace std;

int main(int argc, char **argv)
{
    int opt;
    int digit_optind = 0;
    int option_index = 0;
    /*
     * 形式如“a:b::cd:“，分别表示程序支持的命令行短选项有-a、-b、-c、-d，冒号含义如下：
     * (1)只有一个字符，不带冒号——只表示选项， 如-c 
     * (2)一个字符，后接一个冒号——表示选项后面带一个参数，如-a 100
     * (3)一个字符，后接两个冒号——表示选项后面带一个可选参数，即参数可有可无，如果带参数，则选项与参数直接不能有空格
     * 形式应该如-b200
     */
    char *optstring = "a:b:c:d";

    static struct option long_options[] = {
        /*
         * no_argument (即 0) 表明这个长参数不带参数（即不带数值，如：--name）
         * required_argument (即 1) 表明这个长参数必须带参数（即必须带数值，如：--name Bob）
         * optional_argument（即2）表明这个长参数后面带的参数是可选的，（即--name和--name Bob均可）
         */
        { "reqarg", required_argument, NULL, 'r'},
        { "noarg", no_argument, NULL, 'n'},
        { "optarg", optional_argument, NULL, 'o'},
        { 0, 0, 0, 0}
    };

    /*
     * 如果longindex非空，它指向的变量将记录当前找到参数符合longopts里的第几个元素的描述，即是longopts的下标值。
     * optind表示的是下一个将被处理到的参数在argv中的下标值。
     */
    while((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
    {
        cout << "opt = " << opt << endl;
        cout << "optarg = " << optarg << endl;
        cout << "optind = " << optind << endl;
        cout << "argv[optind -1] = " << argv[optind - 1] << endl;
        cout << "option_index = " << option_index << endl;
    }

    return 0;
}
