#ifndef _OBJECT_
#define _OBJECT_

#include <iostream>
#include "point3D.h"

using namespace std;

class Object {
    private:
        string type;
        float radius;
        Point3D center;
    public:
        Object(){};
        Object(string mType, float mRadius, Point3D mCenter){ 
            this->type = mType;
            this->radius = mRadius;
            this->center = mCenter;
        };
};

#endif