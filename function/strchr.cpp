#include <stdio.h>
#include <string.h>

int main ()
{
   const char str[] = "werkwnrkqwnrknwenr/root/git/CPP_Demo/function";
   const char ch = '/';
   char *ret;

   ret = strchr((char *)str, ch);

   //printf("|%c| 之后的字符串是 - |%s|\n", ch, ret);
   ///root/git/CPP_Demo/function
   printf("%s  \n", ret);
   
   return(0);
}
