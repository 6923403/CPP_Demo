#include <iostream>

class Foo {
    public:
        Foo() {}
        ~Foo() {}
        int a;
};

void do_not_optimize(Foo &v)
{
    std::cout << v.a << std::endl;
}

void do_not_optimize2(const Foo &v)
{
    std::cout << v.a << std::endl;
}

int main()
{
    const int& a = 10; //编译通过
    // int &b = 20; //，编译错误，字面常量是右值
    // do_not_optimize(Foo()); //compile error,函数返回值是临时变量，是右值
    do_not_optimize2(Foo());
    return 0;
}
