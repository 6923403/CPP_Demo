#include <iostream>
#include <vector>
using namespace std;

/*
 * Cplusplus
 * If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
 * If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
 * If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
 */

int main(int argc, char **argv)
{
    vector<int> myvector;
    for(int i = 1; i < 10; i++)
        myvector.push_back(i);

    myvector.resize(5);
    for(auto &s : myvector)
        cout << s << endl;
    cout << endl;

    myvector.resize(8, 100);
    for(auto &s : myvector)
        cout << s << endl;
    cout << endl;

    myvector.resize(12);
    for(auto &s : myvector)
        cout << s << endl;
    cout << endl;

    return 0;
}

