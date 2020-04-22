#ifndef SA_H
#define SA_H

#include <string>
using namespace std;

class Sales_data
{
    friend istream& operator>>(istream &, Sales_data &);
    friend istream& read(istream &, Sales_data &);
    friend ostream& print(ostream &, const Sales_data &);

    public:
        Sales_data();
        ~Sales_data();
        Sales_data& add(const Sales_data&, const Sales_data&);
        Sales_data& combine(const Sales_data&);

        string isbn() const;
        double avg_price() const;

    private:
        string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
};

#endif
