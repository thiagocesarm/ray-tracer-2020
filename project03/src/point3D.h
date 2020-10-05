#ifndef _POINT3D_
#define _POINT3D_

using namespace std;

class Point3D {
    private:
        float x;
        float y;
        float z;
    public:
        Point3D(){};
        Point3D(int mX, int mY, int mZ){ 
            this->x = mX;
            this->y = mY;
            this->z = mZ;
        };
        float getX() const { return this->x; }
        float getY() const { return this->y; }
        float getZ() const { return this->z; }
};

inline Point3D operator-(const Point3D &p1, const Point3D &p2) { return Point3D(p1.getX() - p2.getX(), p1.getY() - p2.getY(), p1.getZ()  - p2.getZ());}

inline Point3D operator+(const Point3D &p1, const Vec3 &v1) { return Point3D(p1.getX() + v1.x(), p1.getY() + v1.y(), p1.getZ()  + v1.z());}

inline Point3D operator*(float t, const Point3D &p) {
    return Point3D(t*p.getX(), t*p.getY(), t*p.getZ());
}

#endif