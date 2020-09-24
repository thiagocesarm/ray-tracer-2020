#ifndef ORTHO_H
#define ORTHO_H

#include "../core/rt3.h"
#include "../core/camera.h"

namespace rt3 {

    /// Orthographic camera implementation (parallel projection)
    class OrthographicCamera : public Camera
    {
        public:
            // === Public interface


            /// Default constructor (Legacy version)
            OrthographicCamera(
                    Point3f lfrom=Point3f{0,0,0},
                    Point3f lat=Point3f{0,0,-1},
                    Vector3f vup=Vector3f{0,1,0},
                    real_type l=0, real_type r=0, real_type b=0, real_type t=0,
                    Film * film=nullptr
                    )
                : Camera( film )
                {
                    this->l = l; // Located at the base class.
                    this->r = r;
                    this->b = b;
                    this->t = t;
                    build_camera_frame( lfrom, lat, vup );
                    set_parallel_box( l, r, b, t );
                }
            // The other special methods are left as default.
            virtual ~OrthographicCamera() = default;
            OrthographicCamera( const OrthographicCamera & ) = default;
            OrthographicCamera & operator=( const OrthographicCamera & ) = default;

            void set_view_plane( void );

            /// Sets the camera for parallel projection.
            /*!
             *  This method sets up the view plane to support parallel projection
             *  (either orthogonal or oblique).
             *  \param l The position of the left edge of the view plane.
             *  \param r The position of the right edge of the view plane.
             *  \param b The position of the bottom edge of the view plane.
             *  \param t The position of the top edge of the view plane.
             *  \param vpn The view plane normal (necessary for non-orthogonal projections). If this parameter is omitted, we assume perpendicular projection.
             */
            void set_parallel_box( float, float, float, float ) ;

            /// Return a ray based on the camera's set up.
            void generate_ray( real_type s, real_type t, Ray& r ) const override;
            void generate_ray( size_type i, size_type j, Ray& r ) const override;
    };

    //=== class related functions.

    /// Regular factory pattern function.
    OrthographicCamera *create_orthographic_camera( const ParamSet &ps, const ParamSet &lookat_ps, Film *film );
}
#endif
//-------------------------------------------------------------------------------
