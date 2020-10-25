#include <stdio.h>

int main()
{
    FILE* fp;
    fp = fopen("1.txt", "w+");

    fputs("123", fp);
    fputs("456", fp);

    fclose(fp);

    return 0;
}
