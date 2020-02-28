#ifndef FBOX_H
#define FBOX_H


class Box
{
    double width;
    public:
    friend void printwidth(Box box);
    void setwidth(double wid);

};

#endif
