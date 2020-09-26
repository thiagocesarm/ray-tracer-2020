#ifndef _CAMERA_
#define _CAMERA_

#include "ray.h"
#include "point3D.h"
#include "vec3.h"

using namespace std;

class Camera {
    private:
        string type;
    public:
        Camera(){};
        Camera(string mType);
        virtual void generate_ray( float ss, float tt, Ray& ray) const = 0;
        virtual void generate_ray( int x, int y, Ray& ray) const = 0;
        
        Point3D eye{0,0,0};  //!< Camera view point (origin).
        Vec3 u{0,1,0};   //!< Camera's X local coordinate system.
        Vec3 v{1,0,0};   //!< Camera's Y local coordinate system.
        Vec3 w{0,0,1};   //!< Camera's Z local coordinate system.
        Vec3 vpn{0,0,-1};//!< Normal to the view plane in case we need oblique projection.

        
        Point3D llc{-1,-1,-1}; //!< The vp's lower left corner, i.e. the vp's origin.
        Vec3 vp_horz_axis{1,0,0}; //!< The vp's horizontal axis: defines the widht of the vp.
        Vec3 vp_vert_axis{0,1,0}; //!< The vp's vertical axis: defines the height of the vp.
        float l,r,b,t; //!< ortographic box dimensions.

        void build_camera_frame( Point3D lf, Point3D la, Point3D vup );
};

Camera::Camera(string mType) {
    type = mType;
}

#endif