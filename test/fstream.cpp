/*
 * 服务器不能创建日志文件 一脸懵逼
 *
 * 2: 假了 服务器不行 本地可以 再分析分析..
 * 3: 解决了
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    char filename[20] = "123.txt";
    ofstream infile;
    infile.open(filename, ios::out);
    if(!infile)
    {
        std::cout << "error " << std::endl;
        exit(-1);
    }
    infile.close();

    return 0;
}
