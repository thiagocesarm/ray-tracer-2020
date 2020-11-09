#ifndef _POINT_LIGHT_
#define _POINT_LIGHT_

#include "../core/light.h"

class PointLight : public Light {
    public:
        Vec3 I;
        Vec3 scale;
        Vec3 from;

        PointLight(Vec3 mI, Vec3 mScale, Vec3 mFrom) : Light(light_type_e::point) {
            I = mI;
            scale = mScale;
            from = mFrom;
        }
        
        Color sample_Li( const Surfel& hit /*in*/, Vec3 *wi/*out*/) override {
            *wi = I;
            Vec3 vecHit { hit.p.getX(), hit.p.getY(), hit.p.getZ() };
            Vec3 pointVec = from - vecHit;
            pointVec = normalize(pointVec);
            return Color{ pointVec.r(), pointVec.g(), pointVec.b() };
        }
};

#endif