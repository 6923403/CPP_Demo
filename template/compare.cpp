#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T, typename U>
int compare(const T &V1, const U &V2)
{
    if(v1 < v2)
        return 1;
    if(v2 < v1)
        return -1;
    return 0;
}

int main(int argc, char **argv)
{
    string v1 = "aaa";
    string v2 = "bbb";

    int q1 = 111;
    int q2 = 100;

    vector<int> w(1, 2, 3, 4);
    vector<int> w2(4, 5, 6);

    cout << compare(v1, v2) << endl;
    cout << compare(q1, q2) << endl;
    cout << compare(w, w2) << endl;
}
