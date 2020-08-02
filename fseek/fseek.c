#include <stdio.h>

/*
 * SEEK_SET: file start head
 * SEEK_CUR: file point
 * SEEK_END: file end
 */

int main()
{
    FILE *fp;

    fp = fopen("1.txt", "w+");
    fputs("this is abcd", fp);

    fseek(fp, 8, SEEK_SET); //n8 modify last abcd...
    fputs("C prog lang", fp);
    fclose(fp);

    return 0;
}

