#ifndef _FLAT_INTEGRATOR_
#define _FLAT_INTEGRATOR_

#include <iostream>
#include "../core/integrator.h"
#include <math.h>

class FlatIntegrator: public SamplerIntegrator {
    public:
        FlatIntegrator(Camera * cam) : SamplerIntegrator(cam) { }

        Color Li(const Ray& ray, const Scene & scene, const Color bkg_color ) const override {
            Color L(0,0,0);
            Surfel isect; // Intersection information.  
            if (!scene.intersect(ray, &isect)) {
                L = bkg_color;
            } else {
                FlatMaterial *fm = dynamic_cast< FlatMaterial *>( isect.primitive->getMaterial() );
                L = fm->getColor();
            }
            return L;
        }
};

#endif
