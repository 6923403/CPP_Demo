#ifndef OPBOX_H
#define OPBOX_H

class Box
{
    public:
        double getVolume(void);
        void setLength(double len);
        void setBreadth(double bre);
        void setHeight(double he);
        
        Box operator+(const Box &);
    private:
        double length;
        double breadth;
        double height;
};

#endif
