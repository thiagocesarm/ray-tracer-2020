#ifndef _FLAT_INTEGRATOR_
#define _FLAT_INTEGRATOR_

#include <iostream>
#include "../core/integrator.h"

class FlatIntegrator: public SamplerIntegrator {
    public:

        // virtual ~FlatIntegrator() = default;

        FlatIntegrator(Camera * cam) : SamplerIntegrator(cam) { }

        Color Li(const Ray& ray, const Scene & scene, const Color bkg_color ) const override {
            return bkg_color;
        }
};

#endif