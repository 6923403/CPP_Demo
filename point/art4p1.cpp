#include <iostream>
#include <string>
using namespace std;

struct you
{
    string first_name;
    string last_name;
    int grade;
    int age;
};


int main(int argc, char **argv)
{
    you s1[1] = {"A", "B", 99, 20};
    you s2 = {"QW", "ER", 88, 19};
    cout << s2.first_name << "   " << s2.grade << endl;

//    cout << s1->first_name << "  " << s1->last_name << "  " << s1->grade << "  " << s1->age << endl;
}
