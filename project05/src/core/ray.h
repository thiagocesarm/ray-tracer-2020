#ifndef _RAY_
#define _RAY_

#include "../core/vec3.h"
#include "../core/point3D.h"


class Ray {
    public:
        mutable float max_t = 10000;
        Ray (const Point3D& origin, const Vec3& direction ) : origin{origin}, direction{direction} { /*empty*/ }
        Vec3 getDirection() const {return direction;}
        Point3D getOrigin() const {return origin;}
        void setDirection(Vec3 direction) {this->direction = direction;}
        void setOrigin(Point3D origin) {this->origin = origin;}
        Point3D operator()(float t) const { 
            Vec3 newVector = direction * t;
            return Point3D(origin.getX() + newVector.x(), origin.getY() + newVector.y(), origin.getZ() + newVector.z()); 
        }
    private:
        Point3D origin; 
        Vec3 direction;
};
#endif