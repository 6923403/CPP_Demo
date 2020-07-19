#include <iostream>
#include <string>
#include <vector>
using namespace std;

void test1()
{
    try{
    vector<int> vec;
    vec.resize(0x10);
    for(int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    if(string{&vec[0], &vec[2]} != "123")
    {
        cout << "true" << endl;
    }
    else
        cout << "false" << endl;
    }
    catch(...)
    {
        cout << "Errore" << endl;
    }
}

int main(int argc, char **argv)
{
    test1();

    return 0;
}
