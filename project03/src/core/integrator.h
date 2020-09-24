#ifndef INTEGRATOR_H
#define INTEGRATOR_H

// core/integrator.h*
#include "rt3.h"

namespace rt3 {

    /// This is the interface all integrators must provide.
    class Integrator {
        public:
            // Integrator Interface
            virtual ~Integrator();
            // SamplerIntegrator Public Methods
            Integrator( std::shared_ptr<const Camera> camera )
                : camera{camera} {/*empty*/}
            /// This is the main loop that traverse the pixels and creates an image.
            virtual void render(const Scene &scene);
            /// Given a ray, this method determines the color for a pixel.
            virtual Spectrum Li(const Ray &ray, const Scene &scene, const ColorXYZ& background_color, int depth=0) const = 0;
            // virtual void preprocess( const Scene &, Sampler & );

            // Pointer to the camera.
            std::shared_ptr<const Camera> camera;
    };

}  // namespace rt3

#endif  // INTEGRATOR_H
