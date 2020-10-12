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
        vector<Primitive *> primitives;
    
    public:
        PrimList(vector<Primitive *> prims) : primitives{ prims } {};

        bool intersect( Ray r, Surfel *sf ) const override {
            return false;
        };

		bool intersect_p( Ray r ) const override {
            for(auto obj : primitives) {
                if (obj->intersect_p(r)) {
                    return true;
                }
            }
            return false;
        };
};

#endif