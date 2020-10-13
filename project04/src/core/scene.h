#ifndef _SCENE_
#define _SCENE_

#include "../core/background.h"
#include "../core/primitive.h"
#include "../core/ray.h"
#include "../core/surfel.h"

using namespace std;

class Scene {
    public:
        Background * background;
        shared_ptr<Primitive> aggregate;

        Scene( Background * bkg, shared_ptr<Primitive> ag)
             : background{ bkg }, aggregate{ ag } { /* empty */ }

        bool intersect( const Ray& r, Surfel *isect ) const {
            return aggregate.get()->intersect(r, isect);
        }

        bool intersect_p( const Ray& r ) const {
            return aggregate.get()->intersect_p(r);
        }
};

#endif