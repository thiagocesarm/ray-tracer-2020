#ifndef _SURFEL_
#define _SURFEL_

#include "../core/point3D.h"
#include "../core/point2D.h"
#include "../core/vec3.h"
#include "../core/primitive.h"

class Primitive;

class Surfel{
	public:
		Surfel(){ /* empty */ };
		Surfel( const Point3D&p,const Vec3&n, const Vec3&wo, float time, 
			const Point2D& uv, const Primitive *pri )
			: p{p}, n{n}, wo{wo}, time{time}, uv{uv}, primitive{pri}
            {/* empty */};

		Point3D p;      
		Vec3 n;     
		Vec3 wo;     
		float time;     
		Point2D uv;     
		const Primitive * primitive = nullptr; 
};

#endif
