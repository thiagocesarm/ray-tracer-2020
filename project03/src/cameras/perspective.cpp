#include "perspective.h"
#include "../core/camera.h"
#include "../core/paramset.h"

namespace rt3 {

    PerspectiveCamera::PerspectiveCamera( const Point3f &look_from,
            const Point3f& look_at, 
            const Point3f& vup,
            float fovy, Film * f ) : Camera{ f }
    {
    }

    void PerspectiveCamera::generate_ray( real_type s, real_type t, Ray& ray ) const
    {
        // TODO
    }
    void PerspectiveCamera::generate_ray( size_type i, size_type j, Ray& ray ) const
    {
        // TODO
    }

    PerspectiveCamera *create_perspective_camera( const ParamSet &camera_ps, const ParamSet &lookat_ps, Film *film )
    {
        // Extract common camera parameters from _ParamSet_
        // Aux function that retrieves info from the ParamSet.
        float fovy      = retrieve( camera_ps, "fovy",      /* default */ float(45.f) );
        auto look_from  = retrieve( lookat_ps, "look_from", /* default */ Point3f{0,0,0} );
        auto look_at    = retrieve( lookat_ps, "look_at",   /* default */ Point3f{0,0,5} );
        auto vup        = retrieve( lookat_ps, "up",       /* default */ Point3f{0,1,0} );

        return new PerspectiveCamera( look_from, look_at, vup, fovy, film );
    }
    
} // namespace rt.

//==============================[ perspective.cpp ]==============================//
