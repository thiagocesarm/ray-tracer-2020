#include "orthographic.h"

namespace rt3 {

    void OrthographicCamera::set_parallel_box( float l_, float r_, float b_, float t_ )
    {
        /*
         * === SETTING THE IMAGE PLANE ===
         *
         * For the orthographic projetion we need to determine the
         * view plane's dimensions based on the 4 values passed in.
         * The view plane may have a normal different from -w.
         * By default, the focal plane is always located at the
         * camera's orgin (m_eye). In fact, it does not matter
         * where the view plane is located, since the rays are
         * parallel.
         *
         */
        // Save view plane normal.
        vpn = w ;

        // TODO

    }


    /// Deprecated
    void OrthographicCamera::generate_ray( real_type s, real_type t, Ray& ray ) const
    {
        // TODO:
    }

    void OrthographicCamera::generate_ray( size_type x, size_type y, Ray& ray ) const
    {
        // // The input coord, (x,y) are expressed in pixel coords, aka **Raster space**.
        // // Calculate the normalivez value (u_int,v_int) correspoding to (x,y).
        // real_type u_int = l + (r-l)*(x+0.5f)/film->m_full_resolution.x;
        // real_type v_int = b + (t-b)*(y+0.5)/film->m_full_resolution.y;
        // // Determine the ray's origin (point on film) within this new UV coord. system. u_int,v_int in [0,1].
        // ray.o = eye + u_int*u + v_int*v;
        // // All rays have the same direction.
        // ray.d = Normalize(vpn);
    }

    /// Legacy version
    OrthographicCamera *create_orthographic_camera( const ParamSet &camera_ps, const ParamSet &lookat_ps, Film *film )
    {
        // Extract Look at information from paramset.
        std::cout << ">>> Inside create_orthographic_camera()\n";
        // Get eye data.
        Point3f look_from  = retrieve( lookat_ps, "look_from", /* default */ Point3f{0,0,0} );
        // Get center data
        Point3f look_at    = retrieve( lookat_ps, "look_at",   /* default */ Point3f{0,0,1} );
        // Get up vector.
        Vector3f vup       = retrieve( lookat_ps, "up",       /* default */ Vector3f{0,1,0} );
        // Get vpdim data.
        std::vector<float> vpdim_vec{-1,1,-1,1}; // default.
        if ( camera_ps.count("vpdim") != 0 )
        {
            vpdim_vec = retrieve( camera_ps, "vpdim",       /* default */ std::vector<float>() );
            if ( vpdim_vec.size()  != 4 )
                RT3_ERROR("\"vpdim\" should have four values");
        }

        return new OrthographicCamera( 
                look_from, look_at, vup,
                vpdim_vec[0], vpdim_vec[1], vpdim_vec[2], vpdim_vec[3], // l, r, b, t
                film );
    }

} // namespace rt.

//==============================[ camera.cpp ]==============================//
