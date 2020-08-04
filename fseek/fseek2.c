#include <stdio.h>

/*
 * SEEK_SET: file start head
 * SEEK_CUR: file point
 * SEEK_END: file end
 */

int main()
{
    FILE *fp;

    fp = fopen("1.txt", "rb");

    fseek(fp, 0, SEEK_END); //n8 modify last abcd...
    printf("fp = %ld \n", ftell(fp));
    fclose(fp);

    return 0;
}

