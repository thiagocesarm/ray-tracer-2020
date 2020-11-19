#ifndef _MATERIAL_
#define _MATERIAL_

#include <iostream>
#include "../core/color.h"
#include "../core/ray.h"
#include "../core/surfel.h"

using namespace std;

class Material {
    public:
        Material(){ /* empty */ };
        virtual void scatter( Surfel * isect, Ray * r ) = 0;
};

#endif