#include "person.h"
#include <cstring>
using namespace std;

/*
 * Person::Person(const string & ln)
{
    lname = ln;
}
*/

/*
 * Person::Person(const char *fn)
{
    strncpy(fname, fn, sizeof(fn));
}
*/

Person::Person(const string & ln, const char *fn)
{
    lname = ln;
    strncpy(fname, fn, sizeof(fn) + 1);
}

void Person::Show() const
{
    cout << lname << endl;
}

void Person::FormalShow() const
{
    cout << fname << endl;
}

