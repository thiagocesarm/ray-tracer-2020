#ifndef _SPHERE_
#define _SPHERE_

#include <iostream>
#include "point3D.h"
#include "primitive.h"
#include "material.h"
#include "scene_xml_params.h"

using namespace std;

class Sphere: public Primitive {
    public:
        float radius;
        Point3D center;

        Sphere(float mRadius, Point3D mCenter, Material * material) : Primitive( ObjectTypes::SPHERE, material ) {
            this->radius = mRadius;
            this->center = mCenter;
        };
};

#endif