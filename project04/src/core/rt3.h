#ifndef _RT3_
#define _RT3_

#include "../core/integrator.h"
#include "../core/material.h"
#include "../core/primitive.h"
#include "../core/scene.h"

class RT3 {
    public:
        // Film film;
        Camera * camera;
        // Background background
        Integrator * integrator;
        Scene * scene;
        // Material * material;
        // vector<Primitive* > objects;
        void run() {
            integrator->render(*scene);
        };
};

#endif