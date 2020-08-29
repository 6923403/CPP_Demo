#include <iostream>
#include <functional>

/*
 * std::ref 用于包装按引用传递的值。
 * std::cref 用于包装按const引用传递的值。 const类型 不可修改
 */

void foo(int & a)
{
    ++a;
}

void foo2(const int & a)
{
    std::cout << "a = " << a << std::endl;
}

void test_function(std::function<void(void)> fun)
{
    fun();
}

int main()
{
    int a = 1;

    std::cout << "a1 = " << a << std::endl;
    test_function(std::bind(foo, a));
    std::cout << "a2 = " << a << std::endl;
    test_function(std::bind(foo, std::ref(a)));
    std::cout << "a3 = " << a << std::endl;
    test_function(std::bind(foo2, std::cref(a)));
    std::cout << "a4 = " << a << std::endl;

    return 0;

}
