#ifndef _CAMERA_
#define _CAMERA_ 

#include "ray.h"
#include "point3D.h"
#include "vec3.h"
#include "film.h"

using namespace std;

class Camera {
    private:
        string type;
        const int* screen_window;
        int fovy;
    public:
        Camera(){};
        Camera( Film *f ) : film{ f }
             { /* empty */ }
        Camera(string mType, const int* mScreen_window, int mFovy);
        Ray generate_ray( float ss, float tt, Ray& ray);
        Ray generate_ray( int x, int y, int width, int height);
        Film *film;
        
        Point3D eye{0,0,0};  //!< Camera view point (origin).
        Vec3 u{0,1,0};   //!< Camera's X local coordinate system.
        Vec3 v{1,0,0};   //!< Camera's Y local coordinate system.
        Vec3 w{0,0,1};   //!< Camera's Z local coordinate system.
        Vec3 vpn{0,0,-1};//!< Normal to the view plane in case we need oblique projection.

        
        Point3D llc{-1,-1,-1}; //!< The vp's lower left corner, i.e. the vp's origin.
        Vec3 vp_horz_axis{1,0,0}; //!< The vp's horizontal axis: defines the widht of the vp.
        Vec3 vp_vert_axis{0,1,0}; //!< The vp's vertical axis: defines the height of the vp.
        float l,r,b,t; //!< ortographic box dimensions.

        vector<Vec3> build_camera_frame( Point3D look_from, Point3D look_at, Vec3 vup ){
            /*
            * === DETERMINE THE CAMERA FRAME ===
            */
            // Set the camera's eye position.
            eye = look_from;
            Point3D newPoint = look_at - look_from;
            Vec3 gaze = Vec3(newPoint.getX(), newPoint.getY(), newPoint.getZ());
            // The camera's orthonormal basis (right hand rule compliance)
            // Remember, a positive w points towards the positive Z axis.
            Vec3 w = normalize(gaze);
            // vup and m_w are on the same plane; we need a vector perpendicular to this plane.
            Vec3 u = normalize( cross( vup, w ) );
            // Finally, we just need the 3rd orthonormal vector of our new camera basis.
            Vec3 v = normalize( cross ( w, u ) );
            Point3D e = look_from;
            // By default, the view plane normal is perpendicular to the camera's w axis.
            vpn = w;
            // [>
            std::cout << "\n\n>>> The Camera frame is:\n";
            std::cout << "    u (" << u.x() << " " << u.y() << " " << u.z() << " )\n";
            std::cout << "    v (" << v.x() << " " << v.y() << " " << v.z() << " )\n";
            std::cout << "    w (" << w.x() << " " << w.y() << " " << w.z() << " )\n\n";

            vector<Vec3> frame;
            frame.push_back(u);
            frame.push_back(v);
            frame.push_back(w);
            return frame;
        }
};

Camera::Camera(string mType, const int *mScreen_window, int mFovy) {
    type = mType;
    screen_window = mScreen_window;
    fovy = mFovy;
}

#endif