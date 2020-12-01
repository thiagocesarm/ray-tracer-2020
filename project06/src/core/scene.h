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
        shared_ptr<Background> background;
        vector<shared_ptr<Light>> lights;
        shared_ptr<Primitive> aggregate;
        vector<shared_ptr<Primitive>> objects;

        Scene( shared_ptr<Background> bkg, shared_ptr<Primitive> ag, vector<shared_ptr<Light>> lights, vector<shared_ptr<Primitive>> objects)
             : background{ bkg }, aggregate{ ag }, lights{ lights }, objects {objects} { /* empty */ }

        bool intersect( const Ray& r, Surfel *isect ) const {
            return aggregate.get()->intersect(r, isect);
        }

        bool intersect_p( const Ray& r ) const {
            return aggregate.get()->intersect_p(r);
        }
};

#endif