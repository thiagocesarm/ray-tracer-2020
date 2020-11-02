#ifndef _FLAT_INTEGRATOR_
#define _FLAT_INTEGRATOR_

#include <iostream>
#include "../core/integrator.h"

class FlatIntegrator: public SamplerIntegrator {
    public:
        FlatIntegrator(Camera * cam) : SamplerIntegrator(cam) { }

        Color Li(const Ray& ray, const Scene & scene, const Color bkg_color ) const override {
            Color L(0,0,0);
            Surfel isect; // Intersection information.  
            if (!scene.intersect(ray, &isect)) {
                L = bkg_color;
            } else {
                // Old approach
                // L = isect.primitive->getMaterial()->getColor();
                
                Point3D light_pos{ 1, 3, 3};     // Point light location    (hardcoded here, for now)
                Vec3 light_I{ 0.9, 0.9, 0.9 };   // Point light Intensity   (hardcoded here, for now)
                Vec3 kd{ 0.9, 0.1, 0.1 };        // Redish diffuse material (hardcoded here, for now)
                Point3D p = light_pos - isect.p; // Determine the vector from the light to the hit point p.
                
                Vec3 l {p.getX(), p.getY(), p.getZ()};  // Make the light vector.
                l = normalize(l);                       // Normalize the light vector.
                
                Vec3 n{ isect.n };             // Normal vector at the point where the ray hit the surface.
                Vec3 result = kd * light_I * max( 0.f, dot( n, l ));
                Color new_color(result.r(), result.g(), result.b());
                // Determining pixel color based on Lambertian Shading only.
                L = new_color;
            }
            return L;
        }
};

#endif