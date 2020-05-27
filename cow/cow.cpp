#include "cow.h"
#include <iostream>
#include <cstring>
using namespace std;

Cow::Cow()
{
    name[0] = '\0';
    hobby = nullptr;
    weight = 0;
}

Cow::Cow(const char * nm, const char * ho, double wt)
{
    strcpy(name, nm);
    hobby = new char [strlen(nm) + 1];
    strcpy(hobby, ho);
    weight = wt;
}

Cow::Cow(const Cow & c)
{
    strcpy(name, c.name);
    hobby = new char[strlen(c.hobby) + 1];
    strcpy(hobby, c.hobby);
    weight = c.weight;
}

Cow & Cow::operator=(const Cow & c)
{
    strcpy(this->name, c.name);
    this->hobby = new char[strlen(c.hobby) + 1];
    strcpy(this->hobby, c.hobby);
    this->weight = c.weight;
    return *this;
}

void Cow::ShowCow() const
{
    cout << name << "  " << *hobby << "  " << weight << endl;
}

Cow::~Cow()
{
    delete []hobby;
    hobby = nullptr;
}

