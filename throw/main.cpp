#include <iostream>
#include <string>
using namespace std;

class Sales_item
{
        friend istream& operator>>(istream &, Sales_item &);
    public:
        Sales_item() = default;

        int isbn()
        {
            return bookNo;
        }

    private:
        int bookNo;
};

istream &operator >>(istream &in, Sales_item &s)
{
    double price;
    in >> s.bookNo;
}

void test1()
{
    Sales_item item1, item2;
    cin >> item1 >> item2;

    if(item1.isbn() == item2.isbn())
    {
        cout << "======" << endl;
    }
    else
    {
        cerr << "Data must refer to same isbn" << endl;
        return -1;
    }
}

int main(int argc, char **argv)
{
    test1();
}
