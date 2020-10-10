#ifndef _INTEGRATOR_
#define _INTEGRATOR_

#include <iostream>

using namespace std;

class Integrator {
    private:
        string type;
    public:
        Integrator(){};
        Integrator(string mType){ 
            this->type = mType;
        };
};

#endif