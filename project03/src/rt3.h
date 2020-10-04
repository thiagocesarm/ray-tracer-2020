#ifndef _RT3_
#define _RT3_

#include "integrator.h"
#include "material.h"
#include "object.h"

class RT3 {
    public:
        Film film;
        Camera camera;
        Background background;
        Integrator integrator;
        Material material;
        vector<Object> objects;
};

#endif