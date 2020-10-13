#ifndef _FLATMATERIAL_
#define _FLATMATERIAL_

#include "../core/material.h"

class FlatMaterial : public Material {
    public:
        Color color;

        FlatMaterial(
            Color color
        ) {
            this->color = color;
        };

        Color getColor() const override {
            return color;
        };
};

#endif