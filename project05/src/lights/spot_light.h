#ifndef _SPOT_LIGHT_
#define _SPOT_LIGHT_

#include "../core/light.h"

class SpotLight : public Light {
    public:
        float I[3];
        float scale[3];
        float from[3];
        float to[3];
        int cutoff;
        int falloff;
        SpotLight(float mI[], float mScale[], float mFrom[], float mTo[], int mCutoff, int mFalloff) : Light(light_type_e::spot) {
            I[0] = mI[0];
            I[1] = mI[1];
            I[2] = mI[2];
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
        Color sample_Li( const Surfel& hit /*in*/, Vec3 *wi/*out*/) override {
            /* TO DO */
            return Color{ 0, 0, 0 };
        }
};

#endif