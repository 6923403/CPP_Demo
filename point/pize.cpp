#include <iostream>
#include <string>
using namespace std;

struct piza
{
    string company;
    int len;
    int height;
};

void te1()
{
    piza re;
    string cm;
    int *p = new int;
    int *q = new int;

    int ln;
    int he;
    cin >> cm >> ln >> he;
    *p = ln;
    *q = he;
    re = {cm, *p, *q};

    cout << re.company << "  " << re.len << "  " << re.height << endl;

    delete p, q;
}

int main(int argc, char **argv)
{

    te1();

    return 0;
}


