#include<iostream>
#include <functional>
 
template<class T>
void com(T arg)
{
	std::cout <<" com = "<< &arg << "\n";
	arg++;
}
 
int main()
{
	int count = 10;
	int  & rcount = count;
	com(count);
	std::cout << count << std::endl;//10
	com(rcount);
	std::cout << "main=" << &rcount << "\n"; 
	std::cout << count << std::endl;//10
	
	com(std::ref(rcount));//传引用
	std::cout << count << std::endl;//11
	
	std::cin.get();
 
}
