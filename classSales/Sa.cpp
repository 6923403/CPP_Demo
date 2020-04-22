#include "Sa.h"

#include <iostream>
#include <string>
using namespace std;

Sales_data::Sales_data()
{}

istream & Sales_data::operator>>(istream &in, Sales_data &s)
{
    in >> s->bookNo >> s->units_sold >> price;
    s->revenue = s->units_sold * price;

    return *this;
}

istream &Sales_data::read(istream &in, Sales_data &item)
{

}

string Sales_data::isbn() const
{
    /*
     *  return this->bookNo
     */

    return bookNo;
}

double Sales_data::avg_price() const
{
    if(units_sold)
        return revenue/units_sold;
    else
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs->units_sold;
    revenue += rhs->revenue;
    return *this;
}

/*
Sales_data::operator+(Sales_data &s1, Sales_data &s2)
{
    S1->
}

ostream &Sales_data::operator<<(ostream &out, Sales_data &q)
{
    out << q->bookNo << " " << q->
}
*/

~Sales_data::Sales_data()
{}
