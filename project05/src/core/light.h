#ifndef _LIGHT_
#define _LIGHT_

#include "color.h"
#include "surfel.h"
#include "vec3.h"

enum class light_type_e : int {
	ambient = 1,
	directional = 2,
	point = 4,
	spot = 8
};

class Light {
	private:
		light_type_e type;
	public:
		virtual ~Light(){};
		Light( light_type_e type ) {
            this->type = type;
        }
		virtual Color sample_Li( const Surfel& hit /*in*/,
								   Vec3 *wi/*out*/) = 0;
};

#endif