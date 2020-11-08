#ifndef _AMBIENT_LIGHT_
#define _AMBIENT_LIGHT_

#include "../core/light.h"

class AmbientLight : public Light {
    public:
        float L[3];
        AmbientLight(float mL[]) : Light(light_type_e::ambient) {
            L[0] = mL[0];
            L[1] = mL[1];
            L[2] = mL[2];
        }
        Color sample_Li( const Surfel& hit /*in*/, Vec3 *wi/*out*/) override {
            Vec3 vecL {L[0], L[1], L[2]};
            *wi = vecL;
            return Color{ L[0], L[1], L[2] };
        }
};

#endif