#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int a = 3;
    cout << data[a] << endl;
    cout << data[a++] << endl;
    cout << "a" << a << endl;;
    cout << data[a] << endl;
    a++;
    cout << data[a] << endl;

    return 0;
}
