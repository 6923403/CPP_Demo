#include <iostream>
using namespace std;

class Shape
{
    public:
        virtual int getarea() = 0;
        void setWidth(int w)
        {
            width = w;
        }

        void setHeight(int h)
        {
            height = h;
        }

    private:

    protected:
        int width;
        int height;
};

class Rectangle: public Shape
{
    public:

    int getarea()
    {
        return (width * height);
    }

};

class Triangle: public Shape
{
    public:
        int getarea()
        {
            return (width * height) / 2;
        }

};

void test1()
{
    Rectangle Rect;
    Triangle Tri;
    Rect.setWidth(5);
    Rect.setHeight(7);
    cout << "Rect: " << Rect.getarea() << endl;

    Tri.setWidth(5);
    Tri.setHeight(7);
    cout << "Tri: " << Tri.getarea() << endl;
}

int main(int argc, char **argv)
{
    test1();
}
