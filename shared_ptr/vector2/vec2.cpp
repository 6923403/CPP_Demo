#include <iostream>
#include <memory>
#include <vector>

using namespace std;

shared_ptr<vector<int>> avec()
{
    return make_shared<vector<int>>();
}

shared_ptr<vector<int>> push_vec(shared_ptr<vector<int>> v)
{
    v->push_back(10);
    v->push_back(12);
    v->push_back(14);

    return v;
}

void show_vec(shared_ptr<vector<int>> v)
{
    for(auto &s : **v)
        cout << s << endl;
}

int main()
{
    shared_ptr<vector<int>> vec = avec();
    push_vec(vec);

    show_vec(vec);
}
