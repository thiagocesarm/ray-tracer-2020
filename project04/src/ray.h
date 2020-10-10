#ifndef _RAY_
#define _RAY_

#include "vec3.h"
#include "point3D.h"


class Ray {
    public:
        Ray (const Point3D& origin, const Vec3& direction ) : origin{origin}, direction{direction} {/*empty*/}
        Vec3 getDirection() const {return direction;}
        Point3D getOrigin() const {return origin;}
        void setDirection(Vec3 direction) {this->direction = direction;}
        void setOrigin(Point3D origin) {this->origin = origin;}
    private:
        Point3D origin; 
        Vec3 direction;
        Point3D operator()(float t) const { 
            Vec3 newVector = direction * t;
            return Point3D(origin.getX() + newVector.x(), origin.getY() + newVector.y(), origin.getZ() + newVector.z()); 
        }
};
#endif