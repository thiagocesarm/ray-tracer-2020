#ifndef _SCENE_
#define _SCENE_

#include "../core/background.h"
#include "../core/primitive.h"
#include "../core/ray.h"
#include "../core/surfel.h"

using namespace std;

class Scene {
    public:
        Background * background; // The background object.
        shared_ptr<Primitive> aggregate; // The scene graph of objects, acceleration structure. 

        Scene( Background * bkg, shared_ptr<Primitive> ag)
             : background{ bkg }, aggregate{ ag }
        {/* empty */}

        // Determines the intersection info; return true if there is an intersection.
        bool intersect( Ray& r, Surfel *isect ) const {
            return aggregate.get()->intersect(r, isect);
        }

        bool intersect_p( Ray& r ) const {
            return aggregate.get()->intersect_p(r);
        }
};

#endif