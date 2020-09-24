#include "flat.h"
#include "../core/camera.h"
#include "../core/film.h"
#include "../core/paramset.h"
#include "../core/scene.h"

namespace rt3 {

    // FlatIntegrator Method Definitions
    Spectrum FlatIntegrator::Li( const Ray &ray, const Scene &scene,
            const ColorXYZ &background_color, int /* not used */ )  const
    {
        // FOr now, it just returns the background color.
        return background_color;
    }

    FlatIntegrator *create_flat_integrator( const ParamSet &, 
            std::shared_ptr< const Camera> camera )
    {
        // Note: This integrator does not need any parameters.
        return new FlatIntegrator{ camera };
    }


}  // namespace pbrt
