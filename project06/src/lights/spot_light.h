#ifndef _SPOT_LIGHT_
#define _SPOT_LIGHT_

#include "../core/light.h"
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

class SpotLight : public Light {
    public:
        Vec3 I;
        Vec3 scale;
        Vec3 from;
        Vec3 to;
        float cutoff;
        float falloff;
        
        SpotLight(Vec3 mI, Vec3 mScale, Vec3 mFrom, Vec3 mTo, float mCutoff, float mFalloff) : Light(light_type_e::spot) {
            I = mI;
            scale = mScale;
            from = mFrom;
            to = mTo;
            cutoff = mCutoff;
            falloff = mFalloff;
        }

        Color sample_Li( const Surfel& hit /*in*/, Vec3 *wi/*out*/) override {
            Vec3 vecHit {hit.p.getX(), hit.p.getY(), hit.p.getZ()};
            Vec3 pointVec = from - vecHit;
            pointVec = normalize(pointVec);

            Vec3 directionalVec = to - from;
            directionalVec = normalize(-directionalVec);

            float theta = acos( dot(pointVec, directionalVec) ) * 180.0 / PI ;
            if (theta < 0) { theta *= -1; }

            if (theta > cutoff) {
                *wi = I * 0.0; //should be in the shadow outside the spotlight
            } else if (theta < falloff){
                *wi = I; //should be in the middle of the spotlight
            } else {
                *wi = I * pow(( 1.0 - (theta - falloff) / (cutoff - falloff) ), 3); // linear interpolation 100% to 0%
            }

            return Color{ pointVec.r(), pointVec.g(), pointVec.b() };
        }
};

#endif