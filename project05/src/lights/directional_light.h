#ifndef _DIRECTIONAL_LIGHT_
#define _DIRECTIONAL_LIGHT_

#include "../core/light.h"

class DirectionalLight : public Light {
    public:
        Vec3 L;
        Vec3 scale;
        Vec3 from;
        Vec3 to;

        DirectionalLight(Vec3 mL, Vec3 mScale, Vec3 mFrom, Vec3 mTo) : Light(light_type_e::ambient) {
            L = mL;
            scale = mScale;
            from = mFrom;
            to = mTo;
        }
        
        Color sample_Li( const Surfel& hit /*in*/, Vec3 *wi/*out*/) override {
            *wi = L;
            Vec3 directionalVec = to - from;
            directionalVec = normalize(-directionalVec);
            return Color{ directionalVec.r(), directionalVec.g(), directionalVec.b() };
        }
};

#endif