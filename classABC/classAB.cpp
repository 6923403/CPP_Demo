#include "iostream"  
using namespace std;  
  
#include<iostream>  
using namespace std;  
  
class Base  
{  
public:  
    virtual void f(float x)  
    {  
        cout<<"Base::f(float)"<< x <<endl;  
    }  
    void g(float x)  
    {  
        cout<<"Base::g(float)"<< x <<endl;  
    }  
};  
  
class Derived : public Base  
{  
public:  
    virtual void f(float x)  
    {  
        cout<<"Derived::f(float)"<< x <<endl;   //多态、覆盖  
    }  
    void g(int x)  
    {  
        cout<<"Derived::g(int)"<< x <<endl;     //隐藏  
    }  
};  
  
int main(void)  
{  
    //定义子类的对象  
    Derived d;  
    // 基类的指针指向子类对象  
    Base *pb = &d;  
    //子类指针指向子类对象  
    Derived *pd = &d;  
  
    //虚函数，是调用所指向对象的函数  
    pb->f(3.14f);   // Derived::f(float) 3.14  
    pd->f(3.14f);   // Derived::f(float) 3.14  
  
    // 非虚函数，根据指针属于基类或子类调用  
    pb->g(3.14f);   // Base::g(float)  3.14  
    pd->g(3.14f);   // Derived::g(int) 3   
  
    Base a;//定义基类的对象  
    Derived *ptr = (Derived *)&a;//子类的指针    
    ptr->f(3.14f);  // Base::f(float)  3.14  
    ptr->g(3.14f); // Derived::g(int) 3   
  
    return 0;  
}  
