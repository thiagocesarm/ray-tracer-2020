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

        bool intersect( const Ray& r, Surfel *sf ) const override {
            float t_hit = 0;
            bool did_intersect = shape->intersect(r, &t_hit, sf);
            if ( did_intersect ) {
                r.max_t = t_hit;
                sf->primitive = this;
            }
            return did_intersect;
        };

		bool intersect_p( const Ray& r ) const override {
            return shape->intersect_p(r);
        };

        Material * getMaterial() const override {
            return material;
        }
};

#endif
