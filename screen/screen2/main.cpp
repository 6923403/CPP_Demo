#include "screen.h"

#include <iostream>
using namespace std;

void test1()
{
    Screen myscreen;
    //char ch = myscreen.get();
    //ch = myscreen.get(0, 0);
    myscreen.move(4, 0).set('#');

}

void test2()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(cout);
    cout << "\n";
    myScreen.display(cout);
    cout << endl;
}

int main(int argc, char **argv)
{
    test2();
}
