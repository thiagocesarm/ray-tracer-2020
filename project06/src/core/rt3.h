#ifndef _RT3_
#define _RT3_

#include "../core/integrator.h"
#include "../core/material.h"
#include "../core/primitive.h"
#include "../core/scene.h"

class RT3 {
    public:
        shared_ptr<Camera> camera;
        shared_ptr<Integrator> integrator;
        shared_ptr<Scene> scene;
        
        void run() {
            integrator->render(*scene);
        };
};

#endif