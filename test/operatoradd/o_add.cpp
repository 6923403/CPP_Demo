
#include<iostream>
using namespace std;

class mint
{
    friend ostream& operator<<(ostream& cout, mint p);
public:
    mint()
    {
        number = 0;
    }
    mint& operator++()
    {
        number++;
        return *this;
    }
    mint operator++(int)
    {
        mint tmp = *this;
        number++;
        return tmp;
    }

private:
    int number;
};

ostream& operator<<(ostream& cout,mint p)
{
    cout << p.number;
    return cout;
}

void text01()
{
    mint p;
    cout << ++(++(++p)) << endl;
    cout << p++<<endl;
    cout << p << endl;
}

int main()
{
    text01();
    return 0;
}