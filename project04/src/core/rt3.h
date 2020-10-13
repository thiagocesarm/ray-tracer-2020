#ifndef _RT3_
#define _RT3_

#include "../core/integrator.h"
#include "../core/material.h"
#include "../core/primitive.h"
#include "../core/scene.h"

class RT3 {
    public:
        Camera * camera;
        Integrator * integrator;
        Scene * scene;
        
        void run() {
            integrator->render(*scene);
        };
};

#endif