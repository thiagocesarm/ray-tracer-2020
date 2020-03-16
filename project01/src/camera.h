#ifndef _CAMERA_
#define _CAMERA_

using namespace std;

class Camera {
    private:
        string type;
    public:
        Camera(){};
        Camera(string mType);
};

Camera::Camera(string mType) {
    type = mType;
}

#endif