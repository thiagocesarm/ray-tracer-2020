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
        Vec3 from;
        string type_string;
	public:
		virtual ~Light(){};
		Light( light_type_e type ) {
            this->type = type;
        }

		light_type_e getType() {
			return type;
		}

        string getTypeString() {return type_string;}
        void setType(string mType) {this->type_string = mType;}
        Vec3 getFrom() {return from;}
        void setFrom(Vec3 vec){from = vec;}
		virtual Color sample_Li( const Surfel& hit /*in*/,
								   Vec3 *wi/*out*/) = 0;
};

#endif