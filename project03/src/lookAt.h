#ifndef _LOOKAT_
#define _LOOKAT_

#include <iostream>
#include "point3D.h"

using namespace std;

class LookAt {
    private:
        Point3D lookAt;
        Point3D lookFrom;
        Point3D up;
    public:
        LookAt(){};
        LookAt(Point3D mLookAt, Point3D mLookFrom, Point3D mUp){ 
            this->lookAt = mLookAt;
            this->lookFrom = mLookFrom;
            this->up = mUp;
        };
};

#endif