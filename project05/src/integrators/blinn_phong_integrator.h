#ifndef _BLINN_PHONG_INTEGRATOR_
#define _BLINN_PHONG_INTEGRATOR_

#include <iostream>
#include "../core/integrator.h"

class BlinnPhongIntegrator: public SamplerIntegrator {
    private:
        int depth;
    public:
        BlinnPhongIntegrator(Camera * cam, int mDepth) : SamplerIntegrator(cam), depth{ mDepth } { }

        Color Li(const Ray& ray, const Scene & scene, const Color bkg_color ) const override {
            /* TO DO */
            return Color(0,0,0);
        }
};

#endif