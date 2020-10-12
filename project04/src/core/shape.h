#ifndef _SHAPE_
#define _SHAPE_

#include "../core/ray.h"
#include "../core/surfel.h"

class Shape {
    public:
        Shape(){ /* empty */ };
        virtual bool intersect( Ray r, float * t_hit, Surfel *sf ) const = 0;
		virtual bool intersect_p( Ray r ) const = 0;
};

#endif