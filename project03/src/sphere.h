#ifndef _SPHERE_
#define _SPHERE_

#include <iostream>
#include "point3D.h"
#include "primitive.h"
#include "scene_xml_params.h"

using namespace std;

class Sphere: public Primitive {
    public:
        float radius;
        Point3D center;

        Sphere(float mRadius, Point3D mCenter) : Primitive( ObjectTypes::SPHERE ) {
            this->radius = mRadius;
            this->center = mCenter;
        };
};

#endif