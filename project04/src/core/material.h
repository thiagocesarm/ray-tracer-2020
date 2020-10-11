#ifndef _MATERIAL_
#define _MATERIAL_

#include <iostream>
#include "../core/color.h"

using namespace std;

class Material {
    public:
        Material(){};
        Material(string mType, Color mColor);
        Color color;
        string type;
};

Material::Material(string mType, Color mColor) {
    type = mType;
    color = mColor;
}

#endif