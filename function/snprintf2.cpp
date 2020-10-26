#include <stdio.h>
#include <string>
using namespace std;

void test2()
{
    char buffer[50];
    char* s = "123456";
    char* k = "abcedfg";

    snprintf(buffer, 255, "%s %s \n", s, k);
    printf("%s", buffer);
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
    test2();
    return 0;
}
