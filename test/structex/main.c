#include <stdio.h>

typedef struct {
    int a;
    short b[2];

}Ex2;

typedef struct Ex
{
    int a;
    char b[3];
    Ex2 c;
    struct EX *d;
};

int main(int argc, char **argv)
{
    Ex x = { 10, "Hi", { 5, { -1, 25 }}, 0};
    Ex *px = &x;

    /*
     * printf("%d \n", px->a);
    printf("%c \n", px->b[0]);
    printf("%d", *px->c.b);
    */

    Ex y;
    x.d = &y;
    y = { 20, "no", { 6, { -2, 22 }}, 0};

    printf("%d \n", px->d->a);

    return 0;
}
