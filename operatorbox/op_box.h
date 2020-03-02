#ifndef OP_BOX_H
#define OP_BOX_H

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
