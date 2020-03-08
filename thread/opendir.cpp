#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
    const char *as[] = {".cpp"};

    DIR *d = opendir(*as);
    if (d == NULL)
    {
        printf("d == NULL");

    }

    struct dirent *entry;
    while((entry = readdir(d)) != NULL)
    {
        puts(entry -> d_name);

    }

    closedir(d);

}
