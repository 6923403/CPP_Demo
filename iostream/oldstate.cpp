#include <iostream>
#include <istream>
using namespace std;

/*
 * void test1()
{
    auto old_state = cin.rdstate(); //save state
    cin.clear();
    process_input(cin);
    cin.setstate(old_state); //init

    cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit); //reset
}
*/

istream& te2(istream &q)
{
    string m;
    auto old_state = q.rdstate();

    while(q >> m && m != "111")
        cout << m << endl;
    q.clear();
    q.setstate(old_state);
    return q;
}

int main(int argc, char **argv)
{
    istream& is = te2(cin);
}
