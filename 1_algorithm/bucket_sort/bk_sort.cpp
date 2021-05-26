#include <iostream>
#include <vector>
int v_size = 0;
int offset = 100;

void sort(std::vector<int> a, std::vector<int> &v)
{
    std::vector<int> bk(offset, 0);
    int i;
    for(i = 0; i < v_size; i++)
    {
        bk[a[i]]++;
    }

    for(i = 0; i < offset; i++)
    {
        while(bk[i] > 0)
        {
            v.push_back(i);
            bk[i]--;
        }
    }

}

void show(std::vector<int> v)
{
    for(auto &s : v)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<int> a = {22,19, 2, 89, 70, 30, 20, 32, 11, 25, 100};
    std::vector<int > v;
    v_size = a.size();

    sort(a, v);
    show(v);

    return 0;
}