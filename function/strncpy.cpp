/*
 * char *strncpy(char *dest, const char *src, size_t n)
 */

#include <stdio.h>
#include <string.h>

int main()
{
    char src[40];
    char dest[6];

    memset(dest, '\0', sizeof(dest));
    strcpy(src, "Relax mentality");
    strncpy(dest, src, 5);
    printf("最终的目标字符串： %s\n", dest);

    return 0;
}
