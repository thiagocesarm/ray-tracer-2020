#ifndef _PRIMITIVE_
#define _PRIMITIVE_

#include <iostream>
#include "material.h"
#include "surfel.h"

using namespace std;

// class Surfel;

class Primitive {
    public:
        string type;
        Material * material;

        Primitive(){ /* empty */ };
        virtual bool intersect( Ray r, Surfel *sf ) const = 0;
		virtual bool intersect_p( Ray r ) const = 0;

};
#endif