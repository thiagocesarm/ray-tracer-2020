#ifndef _AGGREGATE_PRIMITIVE_
#define _AGGREGATE_PRIMITIVE_

#include "../core/ray.h"
#include "../core/primitive.h"
#include "../core/shape.h"

using namespace std;

class AggregatePrimitive: public Primitive {
    public:
        Material * getMaterial() const override {
            std::cout << ">>> ERROR: Called getMaterial() on Aggregate\n";
            return nullptr;
        }
};


class PrimList: public AggregatePrimitive {
    private:
        vector<shared_ptr<Primitive>> primitives;
    
    public:
        PrimList(vector<shared_ptr<Primitive>> prims) : primitives{ prims } {};

        bool intersect( const Ray& r, Surfel *sf ) const override {
            bool did_intersect = false;
            for(auto obj : primitives) {
                did_intersect = did_intersect | obj->intersect(r, sf);
            }
            return did_intersect;
        };

		bool intersect_p( const Ray& r ) const override {
            for(auto obj : primitives) {
                if (obj->intersect_p(r)) {
                    return true;
                }
            }
            return false;
        };

        Bounds3 bounds() const override {
            Bounds3 bounds = Bounds3();
            for(auto prim : primitives) {
                bounds.Union(prim->bounds());
            }
            return bounds;
        };
};

#endif