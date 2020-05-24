#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <ostream>
using namespace std;

namespace VECTOR
{
    class Vector
    {
        public:
            enum Mode{ RECT, POL};

        private:
            double x;
            double y;
            double mag;
            double ang;
            Mode mode;

            //void set_mag();
            //void set_ang();
            void set_x();
            void set_y();

        public:
            Vector();
            Vector(double n1, double n2, Mode form = RECT);
            void reset(double n1, double n2, Mode form = RECT);
            ~Vector();

            double xval() const
            {
                return x;
            }
            
            double yval() const
            {
                return y;
            }

            double magval();
            double angval();
            void polar_mode();
            void rect_mode();

            Vector operator+(const Vector & t) const;
            Vector operator-(const Vector & t) const;
            Vector operator-() const;
            Vector operator*(double n) const;

            friend Vector operator*(double n, const Vector & t);
            friend ostream & operator<<(ostream & os, const Vector & v);
    };
}

#endif
