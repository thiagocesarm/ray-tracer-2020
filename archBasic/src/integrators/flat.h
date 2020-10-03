#ifndef FLAT_H
#define FLAT_H

#include "../core/integrator.h"
#include "../core/rt3-base.h"

namespace rt3 {

    // FlatIntegrator Declarations
    class FlatIntegrator : public Integrator {
        public:
            // FlatIntegrator Public Methods
            FlatIntegrator( std::shared_ptr<const Camera> camera  )
                : Integrator{ camera }
            {/*empty*/}

            virtual Spectrum Li(const Ray &ray, const Scene &scene, const ColorXYZ &background_color=ColorXYZ{0,0,0}, int depth=0 ) const override;
            virtual ~FlatIntegrator(){};
    };

    FlatIntegrator *create_flat_integrator( const ParamSet &ps, std::shared_ptr< const Camera> camera );

}  // namespace pbrt

#endif  // PBRT_INTEGRATORS_WHITTED_H
