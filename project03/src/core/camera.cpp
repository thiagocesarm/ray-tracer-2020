#include "camera.h"

namespace rt3 {

    void Camera::build_camera_frame( Point3f lf, Point3f la, Vector3f vup )
    {
        /*
         * === DETERMINE THE CAMERA FRAME ===
         */
        // // Set the camera's eye position.
        // eye = lf;
        // // The camera's orthonormal basis (right hand rule compliance)
        // // Remember, a positive w points towards the positive Z axis.
        // w = Normalize( la - lf );
        // // vup and m_w are on the same plane; we need a vector perpendicular to this plane.
        // u = Normalize( Cross( vup, w ) );
        // // Finally, we just need the 3rd orthonormal vector of our new camera basis.
        // v = Normalize( Cross( w, u ) );
        // // By default, the view plane normal is perpendicular to the camera's w axis.
        // vpn = w;
        // [>
        // std::cout << "\n\n>>> The Camera frame is:\n";
        // std::cout << "    u (" << u.x << " " << u.y << " " << u.z << " )\n";
        // std::cout << "    v (" << v.x << " " << v.y << " " << v.z << " )\n";
        // std::cout << "    w (" << w.x << " " << w.y << " " << w.z << " )\n\n";
        // */
    }

} // namespace rt.

//==============================[ camera.cpp ]==============================//
