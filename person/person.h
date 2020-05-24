#ifndef PERSON_H_
#define PERSON_H_

using namespace std;

#include <iostream>
#include <string>
class Person
{
    private:
//        static const LIMIT = 25;
        string lname;
        char fname[25];

    public:
        Person()
        { 
            lname = "";
            fname[0] = '\0';
        }
        Person(const string & ln, const char *fn = "abc");
        void Show() const;
        void FormalShow() const;
};

#endif
