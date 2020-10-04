#ifndef _RT3_
#define _RT3_

#include "integrator.h"
#include "material.h"
#include "primitive.h"

class RT3 {
    public:
        // Film film;
        Camera *camera;
        Background background;
        Integrator integrator;
        Material * material;
        vector<Primitive> objects;
};

#endif