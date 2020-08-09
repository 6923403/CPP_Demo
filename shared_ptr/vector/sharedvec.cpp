#include <iostream>
#include <vector>
#include <memory>

std::shared_ptr<std::vector<int>> foo()
{
    return std::make_shared<std::vector<int>>();
}

void push_vec(std::shared_ptr<std::vector<int>> vec)
{
    for(int i = 6; i < 11; ++i)
    {
        vec->push_back(i);
    }

}

void pop_vec(std::shared_ptr<std::vector<int>> vec)
{
    for(auto s : *vec)
    {
        std::cout << s << "  ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    std::shared_ptr<std::vector<int>> vec = foo();
    push_vec(vec);
    pop_vec(vec);

    return 0;
}
