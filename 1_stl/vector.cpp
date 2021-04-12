#include <iostream>
#include <vector>

std::vector<int> vec = {1, 2, 3, 4, 5};

void show(std::vector<int> vec)
{
    for (auto& i : vec)
        std::cout << i << " ";
    std::cout << std::endl;
}

void add()
{
    vec.push_back(6);
}

void insert()
{
    std::vector<int>::iterator it;
    it = vec.begin();
    vec.insert(it + 6, 7);
}

void m_delete()
{
    vec.erase(vec.begin() + 6);

    std::vector<int> vec2(vec);
    std::vector<int>::iterator it = vec2.begin();
    vec2.erase(it + 3, it + 5);
    vec2.clear();
}

void sort()
{
    std::vector<int> vec2 = {44, 32, 12, 35, 66, 77};
    std::vector<int> vec3(vec2);

    //升序
    sort(vec2.begin(), vec2.end());

    //反序
    reverse(vec2.begin(), vec2.end());

    sort(vec3.rbegin(), vec3.rend());
    show(vec3);
}

int main(int argc, char** argv)
{
    add();
    insert();
    m_delete();
    sort();
    return 0;
}