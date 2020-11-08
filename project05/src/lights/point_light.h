#ifndef _POINT_LIGHT_
#define _POINT_LIGHT_

#include "../core/light.h"

class PointLight : Light {
    public:
        float I[3];
        float scale[3];
        float from[3];
        PointLight(float mI[], float mScale[], float mFrom[]) : Light(light_type_e::point) {
            I[0] = mI[0];
            I[1] = mI[1];
            I[2] = mI[2];
            scale[0] = mScale[0];
            scale[1] = mScale[1];
            scale[2] = mScale[2];
            from[0] = mFrom[0];
            from[1] = mFrom[2];
            from[2] = mFrom[2];
        }
        Color sample_Li( const Surfel& hit /*in*/, Vec3 *wi/*out*/) override {
            /* TO DO */
            return Color{ 0, 0, 0 };
        }
};

#endif