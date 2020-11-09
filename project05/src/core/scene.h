#ifndef _SCENE_
#define _SCENE_

#include "../core/background.h"
#include "../core/primitive.h"
#include "../core/ray.h"
#include "../core/surfel.h"
#include "../core/light.h"

using namespace std;

class Scene {
    public:
        Background * background;
        vector<Light *> lights;
        shared_ptr<Primitive> aggregate;

        Scene( Background * bkg, shared_ptr<Primitive> ag, vector<Light *> lights)
             : background{ bkg }, aggregate{ ag }, lights{ lights } { /* empty */ }

        bool intersect( const Ray& r, Surfel *isect ) const {
            return aggregate.get()->intersect(r, isect);
        }

        bool intersect_p( const Ray& r ) const {
            return aggregate.get()->intersect_p(r);
        }
};

#endif