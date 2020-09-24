#include "integrator.h"
#include "scene.h"
#include "camera.h"
#include "background.h"


namespace rt3 {

    // Integrator Method Definitions
    Integrator::~Integrator() {/*empty*/}

    // SamplerIntegrator Method Definitions
    void Integrator::render(const Scene &scene)
    {
        // [1]=== Preprocess the scene
        // preprocess( scene );

        Point2i full_resolution{ camera->film->m_full_resolution };
        int w = full_resolution[0];
        int h = full_resolution[1];
        for ( int j = 0 ; j < h ; j++ )
        {
            for( int i = 0 ; i < w ; i++ )
            {
                // Not shooting rays just yet; so let us sample the background.
                auto color = scene.background->sampleXYZ( Point2f{ float(i)/float(w), float(j)/float(h) } ); // get background color.

                // Add sample contribution to the film
                // Pixel location is in ndc (normalized device coordinates).
                camera->film->add_sample( Point2f{ i/float(w), j/float(h) },  color );
            }
        }

        // [4]=== Save final image after rendering
        camera->film->write_image();
    }
}  // namespace pbrt
