#ifndef _AMBIENT_LIGHT_
#define _AMBIENT_LIGHT_

#include "../core/light.h"

class AmbientLight : public Light {
    public:
        Vec3 L;

        AmbientLight(Vec3 mL) : Light(light_type_e::ambient) {
            L = mL;
        }
        
        Color sample_Li( const Surfel& hit /*in*/, Vec3 *wi/*out*/) override {
            *wi = L;
            return Color{ L.r(), L.g(), L.b() };
        }
};

#endif