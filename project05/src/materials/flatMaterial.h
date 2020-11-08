#ifndef _FLATMATERIAL_
#define _FLATMATERIAL_

#include "../core/material.h"

class FlatMaterial : public Material {
    private:
        Color color;

    public:
        FlatMaterial(
            Color color
        ) {
            this->color = color;
        };

        void scatter( Surfel *isect, Ray *r ) override {
            /* TO DO */
        }

        Color getColor() const {
            return color;
        };
};

#endif