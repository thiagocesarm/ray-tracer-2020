#ifndef _RT3_
#define _RT3_

#include "../core/integrator.h"
#include "../core/material.h"
#include "../core/primitive.h"

class RT3 {
    public:
        // Film film;
        Camera *camera;
        Background background;
        Integrator integrator;
        Material * material;
        vector<Primitive* > objects;
};

#endif