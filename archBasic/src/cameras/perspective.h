#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "../core/rt3.h"
#include "../core/camera.h" 

namespace rt3 {

    /// Perspective camera implementation.
    class PerspectiveCamera : public Camera
    {
        public:
            // === Public interface.

            /// Regular constructor.
            PerspectiveCamera( const Point3f & lf, 
                    const Point3f & la,
                    const Point3f & vup,
                    float fovy, Film * film=nullptr );

            // The other special methods are left as default.
            virtual ~PerspectiveCamera() = default;
            PerspectiveCamera( const PerspectiveCamera & ) = default;
            PerspectiveCamera & operator=( const PerspectiveCamera & ) = default;

            /// Return a ray based on the camera's set up.
            void generate_ray( real_type s, real_type t, Ray& r ) const override;
            void generate_ray( size_type i, size_type j, Ray& r ) const override;

        public:
            //--- View plane information.
    };

    //=== class related functions.

    /// Regular factory pattern function.
    PerspectiveCamera *create_perspective_camera( const ParamSet &ps, const ParamSet &lookat_ps, Film *film );
}
#endif
//-------------------------------------------------------------------------------
