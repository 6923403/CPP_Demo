#include <iostream>
using std::cout;
using std::endl;
using std::cin;

double heman(double a, double b);

int main(int argc, char **argv)
{
    double x, y, z;

    cout << "Enter two numbers: ";
    while(cin >> x >> y)
    {
        try
        {
            z = heman(x, y);
        }
        catch(const char * s)
        {
            cout << s << endl;
            cout << "Enter a new pair of numbers: ";
            continue;
        }

        cout << "Harmonic mean of " << x << " and " << y
                << " is " << z << endl;
        cout << "Enter next set of numbers <q to quit>: ";
    }
    cout << "Bye!" << endl;

    return 0;
}

double heman(double a, double b)
{
    if(a == -b)
        throw "bad hean() arguments: a = -b not allowed ";
    return 2.0 * a * b / (a + b);
}
