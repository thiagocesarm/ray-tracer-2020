#ifndef _INTEGRATOR_
#define _INTEGRATOR_

#include <iostream>
#include "../core/camera.h"
#include "../core/color.h"
#include "../core/scene.h"

using namespace std;

class Integrator {
	public:
		// virtual ~Integrator();
		virtual void render( const Scene& scene ) = 0;
};

class SamplerIntegrator : public Integrator {
	protected:
        Camera * camera;
	public:
		// virtual ~SamplerIntegrator() = default;
		SamplerIntegrator( Camera * cam ) : camera{ cam } {};

		virtual Color Li( const Ray& ray, const Scene& scene, const Color bkg_color ) const = 0;
		
		virtual void preprocess( const Scene& scene ) { /* empty */ };

		virtual void render( const Scene& scene ) {

			auto w = camera->film->getWidth();
			auto h = camera->film->getHeight();

			for (int j = h - 1; j >= 0 ; j--) {
				for (int i = 0 ; i < w ; i++) {
					Ray ray = camera->generate_ray( i, j );
					auto color = scene.background->sample( float(i)/float(w), float(j)/float(h) );
					if (scene.aggregate->intersect_p(ray)) {
						color = Color(255,0,0);
						// color = scene.aggregate->getMaterial()->getColor();
					}
					camera->film->drawPixel(i, j, color);
				}
			}

			camera->film->printToFile();
        };
};


#endif