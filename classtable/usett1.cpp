#include <iostream>
#include "tabt.h"

void te1();

int main(int argc, char **argv)
{
    te1();
    return 0;
}

void te1()
{
    using std::cout;
    using std::endl;
    TableTennisPlayer player1("Tara", "Boomdea", false);
    RatedPlayer rplaayer1(1140, "Mallory", "Duck", true);
    rplaayer1.Name();
    if(rplaayer1.HasTable())
    {
        cout << ": has a table" << endl;
    }
    else
    {
        cout << ": hasn't a table" << endl;
    }
    player1.Name();
    if(player1.HasTable())
    {
        cout << ": has a table" << endl;
    }
    else
    {
        cout << ": hasn't a table" << endl;
    }

    cout << "Name: ";
    rplaayer1.Name();
    cout << "; Rating: " << rplaayer1.Rating() << endl;
}
