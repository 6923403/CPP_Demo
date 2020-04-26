#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

//变长数组类
class Array{
public:
    Array(int len);
    Array(const Array &arr);  //拷贝构造函数
    ~Array();
public:
    int operator[](int i) const { return m_p[i]; }  //获取元素（读取）
    int &operator[](int i){ return m_p[i]; }  //获取元素（写入）
    int length() const { return m_len; }
private:
    int m_len;
    int *m_p;
};

Array::Array(int len): m_len(len){
    m_p = (int*)calloc( len, sizeof(int) );
}

Array::Array(const Array &arr){  //拷贝构造函数
    this->m_len = arr.m_len;
    this->m_p = (int*)calloc( this->m_len, sizeof(int) );
    memcpy( this->m_p, arr.m_p, m_len * sizeof(int) );
}

Array::~Array(){ free(m_p); }

//打印数组元素
void printArray(const Array &arr){
    int len = arr.length();
    for(int i=0; i<len; i++){
        if(i == len-1){
            cout<<arr[i]<<endl;
        }else{
            cout<<arr[i]<<", ";
        }
    }
}

int main(){
    Array arr1(10);
    for(int i=0; i<10; i++){
        arr1[i] = i;
    }
   
    Array arr2 = arr1;
    arr2[5] = 100;
    arr2[3] = 29;
   
    printArray(arr1);
    printArray(arr2);
   
    return 0;
}


/*
 *  result: 
 *  0, 1, 2, 3, 4, 5, 6, 7, 8, 9
 *
 *  0, 1, 2, 29, 4, 100, 6, 7, 8, 9
 */
