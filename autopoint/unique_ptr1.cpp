#include <iostream>
#include <memory>
using namespace std;

unique_ptr<string> demo(const char * s)
{
    unique_ptr<string> temp(new string(s));
    return temp;
}

/*
 * new: auto_ptr, share_ptr, unique_ptr;
 * new[]: only use unique_ptr;
 * ex: unique_ptr<double[]> pda(new double(5));
 */

int main(int argc, char **argv)
{
    unique_ptr<string> ps1, ps2;
    /*
     * ps2 = ps1 is error;
     */
    ps1 = demo("Unin1");
    ps2 = move(ps1);
    ps1 = demo(" and more");

    cout << *ps2 << "  \n" << *ps1 << endl;
}
