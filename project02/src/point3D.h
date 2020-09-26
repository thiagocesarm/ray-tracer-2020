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

#endif