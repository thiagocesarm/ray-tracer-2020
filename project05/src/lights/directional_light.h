#ifndef _DIRECTIONAL_LIGHT_
#define _DIRECTIONAL_LIGHT_

#include "../core/light.h"

class DirectionalLight : public Light {
    public:
        float L[3];
        float scale[3];
        float from[3];
        float to[3];
        DirectionalLight(float mL[], float mScale[], float mFrom[], float mTo[]) : Light(light_type_e::ambient) {
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
        }
        Color sample_Li( const Surfel& hit /*in*/, Vec3 *wi/*out*/) override {
            /* TO DO */
            return Color{ 0, 0, 0 };
        }
};

#endif