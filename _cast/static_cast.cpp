#include <iostream>
#include <vector>

/*
 * double a = 1.1;
 * old: 
 * int n = (int)a;
 * now:
 * int n = static_cast<int>(a); 
 */

struct B 
{
    int m = 0;
    void hello() const
    {
        std::cout << "Hello world, this is B!" << "\n";
    }
};

struct D : B
{
    void hello() const
    {
        std::cout << "Hello world, this is D!" << "\n";
    }
};

enum class E
{
    ONE = 1,
    TWO, 
    THREE
};

enum EU
{
    ONE = 1,
    TWO,
    THREE
};

int main()
{
    int n = static_cast<int>(3.14);
    std::cout << "n = " << n << "\n"; //3
    std::vector<int> v = static_cast<std::vector<int>>(10);
    std::cout << "v.size() = " << v.size() << "\n"; //10
    std::cout << "v1 = " << v[1] << "\n"; //0

    D d;
    B & br = d;
    br.hello();
    D & another_d = static_cast<D&>(br);
    another_d.hello();

    std::vector<int> v2 = static_cast<std::vector<int>&&>(v); //RValue-Reference
    std::cout << "after move, v.size() = " << v.size() << "\n";

    static_cast<void>(v2.size()); //discarded-value expression

    void * nv = &n;
    int * n1 = static_cast<int *>(nv);
    std::cout << "* n1 = " << *n1 << "\n";

    D a[10];
    B * dp = static_cast<B*>(a);

    E e = E::ONE;
    int one = static_cast<int>(e);
    std::cout << one << "\n";

    E e2 = static_cast<E>(one);
    EU eu = static_cast<EU>(e2);

    int D::*pm = &D::m;
    std::cout << br.*static_cast<int B::*>(pm) << "\n";

    void * voidp = &e;
    std::vector<int>* p = static_cast<std::vector<int> *>(voidp);
}
