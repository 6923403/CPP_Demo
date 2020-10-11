#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char *name="long";
	string test=name;
	char *test1="lon\0g"; //3
	char test2[5]="long"; //4
	char test3[]={'l','o','n','g'};//不确定的大小：16
	char *test4=test3;
	const char *data_to_char=test.data();//返回一个非null终止的c字符数组
	cout<<"test的长度"<<test.size()<<endl;
	cout<<"test1的长度"<<strlen(test1)<<endl;
	cout<<"test2的长度"<<strlen(test2)<<endl;
	cout<<"test3的长度"<<strlen(test3)<<endl;
	cout<<"test4的长度"<<strlen(test4)<<endl;
	const char *c_str_char=test.c_str();//返回一个以null终止的c字符数组
	cout<<strlen(c_str_char)<<endl;
}
