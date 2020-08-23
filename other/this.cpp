#include <iostream>
using namespace std;

class Box
{
    public:
        /*
        Box(double l = 2.0, double b = 2.0, double h = 2.0)
        {
            length = l;
            breadth = b;
            height = h;  
        }
        */
        Box(double l, double b, double h):length(l), breadth(b), height(h){}

        double Volume()
        {
            return length * breadth * height;
        }

        int compare(Box box)
        {
            return this->Volume() > box.Volume();
        }

    private:
        double length;
        double breadth;
        double height;

};

void test1()
{
    Box box1(3.3, 1.2, 1.5);
    Box box2(8.5, 6.0, 2.0);

    if(box1.compare(box2))
    {
        cout << "B1 " << endl;
    }
    else
    {
        cout << "B2 " << endl;
    }
}

int main(int argc, char **argv)
{
    test1();

}
