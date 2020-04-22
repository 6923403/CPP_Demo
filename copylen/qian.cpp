/*
 *   http://m.biancheng.net/view/2336.html
 */
 
class Base{
public:
    Base(): m_a(0), m_b(0){ }
    Base(int a, int b): m_a(a), m_b(b){ }
private:
    int m_a;
    int m_b;
};

int main(){
    int a = 10;
    int b = a;  //拷贝

    Base obj1(10, 20);
    Base obj2 = obj1;  //拷贝

    return 0;
}


