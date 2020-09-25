#include <stdio.h>
#include <string.h>
 
int main ()
{
   char src[50], dest[50];
 
   strcpy(src,  "This is source");
   strcpy(dest, "This is destination");
 
   /*
    * char *strcat(char *dest, const char *src)
    */
   strcat(dest, src);

   /*
    * 最终的目标字符串： This is destinationThis is source
    */
   printf("最终的目标字符串： %s \n", dest);
   
   return 0;
}
