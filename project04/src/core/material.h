#ifndef _MATERIAL_
#define _MATERIAL_

#include <iostream>
#include "../core/color.h"

using namespace std;

class Material {
    public:
        Material(){ /* empty */ };
        virtual Color getColor() const = 0;
};

#endif