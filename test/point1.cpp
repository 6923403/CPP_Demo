#include <iostream>

void t1(int **b)
{
    std::cout << "**b = " << **b << std::endl; //b=100
    std::cout << "*b = " << *b << " , b = " << b << std::endl; //*b = &i, b = a地址

    **b = 110;
}

void t2(int *c)
{
    std::cout << "*c = " << *c << " , c = " << c << " , &c = " << &c << std::endl;

    *c = 120;
}

int main(int argc, char **argv)
{
    int i = 100;
    std::cout << "&i = " << &i << std::endl;
    int* a = &i;
    std::cout << "*a = " << *a << ", a = " << a << "  , &a = " << &a << std::endl;

    t1(&a);
    std::cout << "*a = " << *a << " , a = " << a << std::endl;
    std::cout << "i = " << i << std::endl;

    t2(a);
    std::cout << "*a = " << *a << " , a = " << a << std::endl;
    std::cout << "i = " << i << std::endl;

    int k = 200;
    *a = k;
    std::cout << "*a = " << *a << " , a = " << a << " , &a = " << " , i = " << i << " , k = " << k << std::endl;

    int m = 300;
    a = &m;
    std::cout << "*a = " << *a << " , a = " << a << " , &a = " << &a << std::endl;
    std::cout << "i = " << i << " , k = " << k << " , m = " << m << std::endl; 

    return 0;
}

/*
&i = 0x7ffee7f77b0c
*a = 100, a = 0x7ffee7f77b0c  , &a = 0x7ffee7f77b00
**b = 100
*b = 0x7ffee7f77b0c , b = 0x7ffee7f77b00
*a = 110 , a = 0x7ffee7f77b0c
i = 110
*c = 110 , c = 0x7ffee7f77b0c , &c = 0x7ffee7f77a98
*a = 120 , a = 0x7ffee7f77b0c
i = 120
*a = 200 , a = 0x7ffee7f77b0c , &a =  , i = 200 , k = 200
*a = 300 , a = 0x7ffee7f77af8 , &a = 0x7ffee7f77b00
i = 200 , k = 200 , m = 300
*/
