#include <iostream>

class type
{
    public:
        int i;
        type() : i(3)
        {}

        void f(int v) const 
        {
            const_cast<type *>(this)->i = v;
        }
};

int main()
{
    int i = 3;
    const int & rci = i;
    const_cast<int &>(rci) = 4;
    std::cout << "i = " << i << "\n";

    type t;
    t.f(4);
    std::cout << "type::i = " << t.i << "\n";

    const int j = 3;
    int * pj = const_cast<int *>(&j);
    std::cout << *pj << std::endl;

    /*
     * compile error: const_cast does not work on function pointers
     */
    void (type::* pmf)(int) const = &type::f; // pointer to member function
    // const_cast<void(type::*)(int)>(pmf);  
}
