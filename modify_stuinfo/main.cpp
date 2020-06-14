
#include <iostream>

#include "CStudent.h"
#include "Cpeople.h"

using namespace std;

int main(int argc, char **argv)
{
	CStudent stu1(16, 29, 3, (char *) "уехЩ");
	stu1.CaculateAverageScore();
	cout << stu1 << endl;
	return 0;
}
