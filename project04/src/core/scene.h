#ifndef _SCENE_
#define _SCENE_

#include "../core/primitive.h"
#include "../core/surfel.h"
#include "../core/background.h"

using namespace std;

class Scene {
    // //=== Public data
    // public:
    //     //std::vector<shared_ptr<Light>> lights; // list of lights
    //     std::shared_ptr< Background > background; // The background object.
    // private:
    //     vector<Primitive *> aggregate; // The scene graph of objects, acceleration structure.

    // //=== Public interface
    // public:
    //     Scene( std::shared_ptr<Primitive> ag, std::unique_ptr< Background > bkg)
    //          : background{bkg}, aggregate{ag}
    //     {/* empty */}
    //     /// Determines the intersection info; return true if there is an intersection.
    //     bool intersect( const Ray& r, Surfel *isect ) const;
    //     /*! A faster version that only determines whether there is an intersection or not;
    //      * it doesn't calculate the intersection info.
    //      */
    //     bool intersect_p( const Ray& r ) const;

};

#endif