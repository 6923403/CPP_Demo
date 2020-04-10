#include <stdio.h>

int compare(int x, int y)
{
    int k = 5;
    if(x > y)
        return k > x? k:x;
    else
        return k > y? k:y;
}

int main()
{
    int a, b, c, d;
    int (*p)(int, int) = &compare;

    scanf("%d %d %d", a, b, c);

    d = p((a, b), c);

    printf("\nsum=  %d\n", d);
}
