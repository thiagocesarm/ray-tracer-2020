#ifndef _MATERIAL_
#define _MATERIAL_

#include <iostream>
#include "color.h"

using namespace std;

class Material {
    private:
        string type;
        Color color;
    public:
        Material(){};
        Material(string mType, Color mColor){ 
            this->type = mType;
            this->color = mColor;
        };
};

#endif