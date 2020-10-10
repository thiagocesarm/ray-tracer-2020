#ifndef _POINT2D_
#define _POINT2D_

using namespace std;

class Point2D {
    private:
        float x;
        float y;
    public:
        Point2D(){};
        Point2D(int mX, int mY){ 
            this->x = mX;
            this->y = mY;
        };
        float getX() const { return this->x; }
        float getY() const { return this->y; }
};

#endif