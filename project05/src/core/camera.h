#ifndef _CAMERA_
#define _CAMERA_ 

#include "../core/ray.h"
#include "../core/point3D.h"
#include "../core/vec3.h"
#include "../core/film.h"

using namespace std;

class Camera {    
    public:
        string type;
        Film *film;
        Point3D eye{0,0,0};  //!< Camera view point (origin).
        Vec3 u{1,0,0};   //!< Camera's X local coordinate system.
        Vec3 v{0,1,0};   //!< Camera's Y local coordinate system.
        Vec3 w{0,0,1};   //!< Camera's Z local coordinate system.
        Vec3 view_plane_normal{0,0,-1};   //!< Normal to the view plane.

        float l, r, b, t; //!< Screen window dimensions.
        Point3D llc{-1,-1,-1}; //!< The vp's lower left corner, i.e. the vp's origin.
        Vec3 vp_horz_axis{1,0,0}; //!< The vp's horizontal axis: defines the widht of the vp.
        Vec3 vp_vert_axis{0,1,0}; //!< The vp's vertical axis: defines the height of the vp.

        Camera() { /* empty */ };
        Camera( Film *f ) : film{ f } { /* empty */ }
        Camera( string t ) : type{ t } { /* empty */ }
        virtual Ray generate_ray( int i, int j ) = 0;
        virtual void finishSetup() = 0;

        vector<Vec3> build_camera_frame( Point3D look_from, Point3D look_at, Vec3 vup ){
            eye = look_from;
            Point3D gazePoint = look_at - look_from;
            Vec3 gaze = Vec3(gazePoint.getX(), gazePoint.getY(), gazePoint.getZ());
            // The camera's orthonormal basis (left hand rule compliance)
            // Positive w pointing towards the positive Z axis.
            w = normalize(gaze);
            // vup and w are on the same plane; we need a vector perpendicular to this plane.
            u = normalize( cross( w, vup ) );
            // Finally, we just need the 3rd orthonormal vector of our new camera basis.
            v = normalize( cross ( w, u ) );
            // By default, the view plane normal is perpendicular to the camera's w axis.
            view_plane_normal = w;
            
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

#endif