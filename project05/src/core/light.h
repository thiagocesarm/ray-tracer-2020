#ifndef _LIGHT_
#define _LIGHT_

#include <iostream>
#include <sstream>

using namespace std;

class Light {
    private:
        string type;
        float L[3];
        int scale [3];
        float from [3];
        float to [3];
        float I[3];
        int cutoff;
        int falloff;
    public:
        Light(){};
        Light(string, float[3], float[3], int[3], float [3], float[3], int, int);
};

Light::Light(string mtype, float mI[], float mL[], int mScale[], float mFrom [], float mTo [], int mCutoff, int mFalloff) {
    type = mtype;
    I[0] = mI[0];
    I[1] = mI[1];
    I[2] = mI[2];
    L[0] = mL[0];
    L[1] = mL[1];
    L[2] = mL[2];
    scale[0] = mScale[0];
    scale[1] = mScale[1];
    scale[2] = mScale[2];
    from[0] = mFrom[0];
    from[1] = mFrom[2];
    from[2] = mFrom[2];
    to[0] = mTo[0];
    to[1] = mTo[1];
    to[2] = mTo[2];
    cutoff = mCutoff;
    falloff = mFalloff;
}

#endif