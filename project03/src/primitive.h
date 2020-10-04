#ifndef _PRIMITIVE_
#define _PRIMITIVE_

#include <iostream>

using namespace std;

class Primitive {
    public:
        string type;
        Primitive( string t ) : type{ t }{ };
};
#endif