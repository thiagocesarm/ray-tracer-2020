#ifndef _FLATMATERIAL_
#define _FLATMATERIAL_

#include "../core/material.h"


class FlatMaterial : public Material {
    public:
        FlatMaterial(
            Color color
        ) {
            this->color = color;
        };
};

#endif