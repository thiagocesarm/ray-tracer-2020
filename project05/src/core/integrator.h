#ifndef _INTEGRATOR_
#define _INTEGRATOR_

#include <iostream>
#include "../core/camera.h"
#include "../core/color.h"
#include "../core/scene.h"

using namespace std;

class Integrator {
	public:
		virtual void render( const Scene& scene ) = 0;
};

class SamplerIntegrator : public Integrator {
	protected:
        Camera * camera;
	public:
		SamplerIntegrator( Camera * cam ) : camera{ cam } {};

		virtual Color Li( const Ray& ray, const Scene& scene, const Color bkg_color ) const = 0;
		
		virtual void preprocess( const Scene& scene ) { /* empty */ };

		virtual void render( const Scene& scene ) {

			auto w = camera->film->getWidth();
			auto h = camera->film->getHeight();

			for (int j = h - 1; j >= 0 ; j--) {
				for (int i = 0 ; i < w ; i++) {
					Ray ray = camera->generate_ray( i, j );
					Surfel isect;

					auto bkg_color = scene.background->sample( float(i)/float(w), float(j)/float(h) );
					auto pixel_color = Li(ray, scene, bkg_color);

					camera->film->drawPixel(i, j, pixel_color);
				}
			}

			camera->film->printToFile();
        };
};

#endif