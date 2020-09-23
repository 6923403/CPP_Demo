#include <stdio.h>
#include <string.h>

/*
 * char *strcpy(char *dest, const char *src)
 */

int main()
{
   char src[40];
   char dest[100];

   memset(dest, '\0', sizeof(dest));
   strcpy(src, "Relax mentality");
   strcpy(dest, src);

   printf("最终的目标字符串： %s\n", dest);

   return 0;
}
