#include <iostream>
#include <vector>
#include <memory>

using namespace std;

vector<int> * avec()
{
    return new vector<int>{1, 2, 3, 4};
}

vector<int> * vecpush(vector<int> *v)
{
    v->push_back(11);
    v->push_back(12);
    v->push_back(13);

    return v;
}

void showvec(vector<int> *v)
{
    for(auto &s : v)
    {
        cout << s << endl;
    }

    delete v;
}

int main(int argc, char **argv)
{
    vector<int> *vec = avec();

    vecpush(vec);

    showvec(vec);

    return 0;
}
