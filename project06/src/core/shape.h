#ifndef _SHAPE_
#define _SHAPE_

#include "../core/ray.h"
#include "../core/surfel.h"
#include "../core/bounds3.h"

class Shape {
    public:
        Shape(){ /* empty */ };
        virtual bool intersect( const Ray& r, float * t_hit, Surfel *sf ) const = 0;
		virtual bool intersect_p( const Ray& r ) const = 0;
        virtual Bounds3 bounds() const = 0;
};

#endif