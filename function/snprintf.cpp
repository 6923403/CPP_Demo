#include <stdio.h>
#include <string>
using namespace std;

void test2()
{
    char buffer[50];
    char* s = "runooabcd";

    // 读取字符串并存储在 buffer 中
    int j = snprintf(buffer, 6, "%s\n", s);

    // 输出 buffer及字符数
    printf("string:\n%s\ncharacter count = %d\n", buffer, j);

    /*
     * string:
     * runoo
     * character count = 10
    */
}

int main()
{
    /*
     * int snprintf ( char * str, size_t size, const char * format, ... );
     * str -- 目标字符串。
     * size -- 拷贝字节数(Bytes)。
     * format -- 格式化成字符串。
     * ... -- 可变参数。
     *
     *
     * (1) 如果格式化后的字符串长度小于等于 size，则会把字符串全部复制到 str 中，并给其后添加一个字符串结束符 \0；
     * (2) 如果格式化后的字符串长度大于 size，超过 size 的部分会被截断，只将其中的 (size-1) 个字符复制到 str 中，并给其后添加一个字符串结束符 \0，返回值为欲写入的字符串长度。
     */
    char buffer[100];
    int cx;

    cx = snprintf(buffer, 100, "The half of %d is %d", 60, 60/2);

    if(cx>=0 && cx<100)      // check returned value
        snprintf(buffer+cx, 100-cx, ", and the half of that is %d.", 60/2/2 );
    puts(buffer);


    test2();
    return 0;
}
