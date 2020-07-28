#include <stdio.h>
#include <stdarg.h>

/*
 * https://www.runoob.com/cprogramming/c-function-vsprintf.html
 */

char buffer[80];

int editorSetstatus(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret;
    ret = vsnprintf(buffer, sizeof(buffer - 1), fmt, ap);

    va_end(ap);

    return (ret);
}

int main(int argc, char **argv)
{
    int len = 20;
    editorSetstatus("%d", len);

    printf("%s \n", buffer);

    return 0;
}

