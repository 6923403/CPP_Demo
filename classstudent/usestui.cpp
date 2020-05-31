#include <iostream>
#include "studenti.h"
using namespace std;

void set(Student & sa, int n);
const int pupils = 3;
const int quizzes = 5;

int main()
{
    Student ada[pupils] = {Student(quizzes), Student(quizzes), Student(quizzes)};

    int i;
    for(i = 0; i < pupils; i++)
        set(ada[i], quizzes);

    cout << "Done." << endl;

    return 0;
}

void set(Student & sa, int n)
{
    cout << "Please enter name: ";
    getline(cin, sa);
    cout << "Please enter " << n << " quiz scores: \n";
    for(int i = 0; i < n; i++)
        cin >> sa[i];
    while(cin.get() != '\n')
        continue;
}


