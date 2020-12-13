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
            auto t1 = std::chrono::high_resolution_clock::now();
            integrator->render(*scene);
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
            cout << "\n>>> SCENE RENDERING execution time: " << duration << " ms \n";
        };
};

#endif