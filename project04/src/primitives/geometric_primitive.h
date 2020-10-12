#ifndef _GEOMETRIC_PRIMITIVE_
#define _GEOMETRIC_PRIMITIVE_

#include "../core/ray.h"
#include "../core/primitive.h"
#include "../core/shape.h"

class GeometricPrimitive: public Primitive {
    public:
        Shape * shape;
        Material * material;

        GeometricPrimitive(Shape * s, Material * m) : shape{s}, material{m} {};

        bool intersect( Ray r, Surfel *sf ) const override {
            return shape->intersect(r, &r.max_t,  sf);
        };

		bool intersect_p( Ray r ) const override {
            return shape->intersect_p(r);
        };

        Material * getMaterial() const override {
            return material;
        }
};

#endif
