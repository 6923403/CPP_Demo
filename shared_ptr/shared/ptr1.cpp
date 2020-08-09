#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

int main(int argc, char **argv)
{
    std::shared_ptr<std::string> p1;
    std::shared_ptr<std::list<int>> p2;

    if(p1 && p1->empty())
    {
        *p1 = "hi";
    }

    std::shared_ptr<int> p3 = std::make_shared<int>(42);
    std::shared_ptr<std::string> p4 = std::make_shared<std::string>(10, '9');
    std::shared_ptr<int> p5 = std::make_shared<int>();

    //p6 allocate vector<string>
    auto p6 = std::make_shared<std::vector<std::string>>();
}
