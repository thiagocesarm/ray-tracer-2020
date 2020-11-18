#ifndef _PRIMITIVE_
#define _PRIMITIVE_

#include <iostream>
#include "../core/material.h"
#include "../core/surfel.h"
#include "../core/material.h"
#include "../core/bounds3.h"

using namespace std;

class Primitive {
    public:
        Primitive(){ /* empty */ };
        virtual ~Primitive() = default;
        virtual bool intersect( const Ray& r, Surfel *sf ) const = 0;
		virtual bool intersect_p( const Ray& r ) const = 0;
        virtual Material * getMaterial() const = 0;
        virtual Bounds3 bounds() const = 0;

};
#endif