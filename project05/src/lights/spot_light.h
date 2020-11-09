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
        int cutoff;
        int falloff;
        
        SpotLight(Vec3 mI, Vec3 mScale, Vec3 mFrom, Vec3 mTo, int mCutoff, int mFalloff) : Light(light_type_e::spot) {
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

            float theta = dot(pointVec, directionalVec);

            float cutoffCoss = cos(cutoff * PI / 180.0);
            float falloffCoss = cos(falloff * PI / 180.0);

            if (theta <= cutoffCoss) {
                *wi = I * 0.0; //should be in the shadow outsite the spotlight
            } else if (theta >= falloffCoss){
                *wi = I * 1.0; //should be in the middle of the spotlight
            } else {
                float intensity = (theta - falloffCoss)/cutoffCoss - falloffCoss;
                *wi = I * intensity;
            }

            return Color{ vecHit.r(), vecHit.g(), vecHit.b() };
        }
};

#endif