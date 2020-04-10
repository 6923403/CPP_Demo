#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
    public:
        void setWidth(int w);
        void setHeight(int h);

    protected:
        int width;
        int height;

};

class PaintCost
{
    public:
        int getCost(int area);
};

class Rectangle:public Shape, public PaintCost
{
    public:
        int getArea();
};

#endif
