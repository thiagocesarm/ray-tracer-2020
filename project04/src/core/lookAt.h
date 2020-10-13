#ifndef _LOOKAT_
#define _LOOKAT_

#include <iostream>
#include "../core/point3D.h"

using namespace std;

class LookAt {
    public:
        Point3D lookFrom;
        Point3D lookAt;
        Vec3 up;
        
        LookAt(){};
        LookAt(Point3D mLookFrom, Point3D mLookAt, Vec3 mUp){ 
            this->lookFrom = mLookFrom;
            this->lookAt = mLookAt;
            this->up = mUp;
        };
};

#endif