#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    using namespace std;
    int updates = 6;
    int *p_updates;
    p_updates = &updates;
    *p_updates + 1;
    cout << updates << endl;
    cout << *p_updates << endl;

}
