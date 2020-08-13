//return *this返回的是当前对象的克隆或者本身（若返回类型为A， 则是克隆， 若返回类型为A&， 则是本身 ）。return this返回当前对象的地址（指向当前对象的指针）
#include <iostream>
using namespace std;
 
class A
{
public:
	int x;
	A* get()
	{
		return this;
	}
};
 
int main()
{
	A a;
	a.x = 4;
 
	if(&a == a.get())
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" << endl;
	}
 
	return 0;
}
