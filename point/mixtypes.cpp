#include <iostream>
using namespace std;

struct an_year
{
    int year;
};

int main(int argc, char **argv)
{
    an_year s1, s2, s3;
    s1.year = 1991;
    an_year * pa = &s2;
    pa->year = 1992;
    an_year to[3];
    to[0].year = 2001;
    cout << to->year << endl;
    const an_year * arp[3] = {&s1, &s2, &s3};
    cout << arp[1]->year << endl;
    const an_year ** ppa = arp;
    auto ppb = arp; //an_year **ppb = arp
    cout << (*ppa)->year << endl;
    cout << (*(ppb + 1))->year << endl;

    return 0;
}
