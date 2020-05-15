#include <iostream>
using namespace std;

void te1()
{
    cout << "a" << endl; //输出 a 和 换行 然后刷新缓冲区
    cout << "a" << flush;//输出a 然后刷新缓冲区 不附加任何其他东西
    cout << endl << " a" << ends << "b";//输入a 和一个空字符' ' 然后刷新
    cout << unitbuf;//所有输出操作后都会立即刷新缓冲区
    cout << nounitbuf;//回到正常缓冲方式
}

void te2()
{
    cin.tie(&cout);
    ostream *old_tie = cin.tie(nullptr);

    cin.tie(&cerr);
    cin.tie(old_tie);
}

int main(int argc, char **argv)
{
    te2();
}

