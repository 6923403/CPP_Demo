//http://c.biancheng.net/view/3741.html
/*
 * [] 不捕获任何变量。
 * [&] 捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获）。
 * [=] 捕获外部作用域中所有变量，并作为副本在函数体中使用（按值捕获）。
 * [=，&foo] 按值捕获外部作用域中所有变量，并按引用捕获 foo 变量。
 * [bar] 按值捕获 bar 变量，同时不捕获其他变量。
 * [this] 捕获当前类中的 this 指针，让 lambda 表达式拥有和当前类成员函数同样的访问权限。如果已经使用了 & 或者 =，就默认添加此选项。捕获 this 的目的是可以在 lamda 中使用当前类的成员函数和成员变量。
 */

#include <iostream>

class A
{
public:
    int i_ = 0;
    void func(int x, int y)
    {
        //auto x1 = []{ return i_; };                    // error，没有捕获外部变量
        auto x2 = [=]{ return i_ + x + y; };           // OK，捕获所有外部变量
        auto f2 = [=]() mutable { return i_ + x + y; };    //lambda 表达式按值捕获了所有外部变量。在捕获的一瞬间，a 的值就已经被复制到f中了。之后 a 被修改，但此时 f 中存储的 a 仍然还是捕获时的值，因此，最终输出结果是 0。如果希望 lambda 表达式在调用时能够即时访问外部变量，我们应当使用引用方式捕获。
        auto x3 = [&]{ return i_ + x + y; };           // OK，捕获所有外部变量
        auto x4 = [this]{ return i_; };                // OK，捕获this指针
        //auto x5 = [this]{ return i_ + x + y; };        // error，没有捕获x、y
        auto x6 = [this, x, y]{ return i_ + x + y; };  // OK，捕获this指针、x、y
        auto x7 = [this]{ return i_++; };              // OK，捕获this指针，并修改成员的值
        std::cout << x2() << std::endl;
        std::cout << f2() << std::endl;
        std::cout << x3() << std::endl;
        std::cout << x4() << std::endl;
        std::cout << x6() << std::endl;
        std::cout << x7() << std::endl;
        std::cout << x7() << std::endl;
    }
};

int main(int argc, char** argv)
{
    auto f = [](int a) -> int { return a + 1; };
//    std::cout << f(1) << std::endl;  // 输出: 2
    A a;
    a.func(0, 1);


    return 0;
}