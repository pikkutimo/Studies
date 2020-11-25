#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "random.h"

enum Plane_status {null, arriving, departing};

class Plane {
    public:
        Plane( );
        Plane(int flt, int time, Plane_status status);
        void refuse( ) const;
        void hailmary() const;
        bool land(int time);
        void fly(int time) const;
        int started( ) const;
        int checkFuel();
        void setFuel();
    private:
        int flt_num;
        int clock_start;
        int fuel; // How many time units the plane can stay airborne
        Plane_status state;
};

#endif