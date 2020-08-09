#include <iostream>
#include <vector>
#include <memory>

using std::vector;

vector<int> * foo()
{
    return new vector<int> {1, 2, 3, 4, 5};
}

void push_vec(vector<int> * vec)
{
    for(int i = 6; i < 11; ++i)
    {
        vec->push_back(i);
    }

}

void pop_vec(vector<int> * vec)
{
    for(auto &s : *vec)
    {
        std::cout << s << "  ";
    }

    std::cout << std::endl;

    delete vec;
}

int main(int argc, char **argv)
{

    vector<int> * vec = foo();
    push_vec(vec);
    pop_vec(vec);
#if 0
    vector<int> * vec;
    foo(vec);
    push_vec(vec);
    pop_vec(vec);
#endif

    return 0;
}
