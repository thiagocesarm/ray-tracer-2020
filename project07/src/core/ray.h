#ifndef _RAY_
#define _RAY_

#include <limits>
#include "../core/vec3.h"
#include "../core/point3D.h"


class Ray {
    public:
        mutable float max_t = std::numeric_limits<float>::max();
        mutable float min_t = 0;
        Ray () : origin{ Point3D(0, 0, 0)}, direction{ Vec3(1, 1, 1) } { /* empty*/ }
        Ray (const Point3D& origin, const Vec3& direction ) : origin{origin}, direction{direction} { /*empty*/ }
        Ray (const Point3D& origin, const Vec3& direction, float t_min, float t_max) : origin{origin}, direction{direction}, min_t(t_min), max_t(t_max) { /*empty*/ }
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