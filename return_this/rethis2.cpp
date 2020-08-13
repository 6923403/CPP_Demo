#include <iostream>
using namespace std;
 
class A
{
public:
	int x;
	A get()
	{
		return *this; //返回当前对象的拷贝
	}

	A& get()
	{
		return *this; //返回当前对象
        //return yes
	}
};
 
int main()
{
	A a;
	a.x = 4;
 
	if(a.x == a.get().x)
	{
		cout << a.x << endl;
	}
	else
	{
		cout << "no" << endl;
	}
 
	if(&a == &a.get())
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" << endl;
	}
 
	return 0;
}
