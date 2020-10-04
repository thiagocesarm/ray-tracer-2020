#ifndef _PRIMITIVE_
#define _PRIMITIVE_

#include <iostream>
#include "material.h"

using namespace std;

class Primitive {
    public:
        string type;
        Material * material;

        Primitive( string t, Material * m ) : type{ t }, material { m }{ };
};
#endif