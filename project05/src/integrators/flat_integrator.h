#ifndef _FLAT_INTEGRATOR_
#define _FLAT_INTEGRATOR_

#include <iostream>
#include "../core/integrator.h"
#include <math.h>

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
                // FlatMaterial *fm = dynamic_cast< FlatMaterial *>( isect.primitive->getMaterial() );
                // L = fm->getColor();

                Point3D light_pos{ 1, 3, 3};     // Point light location    (hardcoded here, for now)
                Vec3 light_I{ 0.9, 0.9, 0.9 };   // Point light Intensity   (hardcoded here, for now)
                Vec3 light_IA{ 0.9, 0.9, 0.9 };   // ambient information from parser
                Vec3 kd{ 0.9, 0.1, 0.1 };        // Redish diffuse material (hardcoded here, for now)
                Point3D p = light_pos - isect.p; // Determine the vector from the light to the hit point p.
                
                Vec3 l {p.getX(), p.getY(), p.getZ()};  // Make the light vector.
                l = normalize(l);                       // Normalize the light vector.

                Vec3 ks{ 0.9, 0.1, 0.1 }; // coeficiente que vem do arquivo de cena;
                Vec3 ka{ 0.9, 0.1, 0.1 };  // coeficiente que vem do arquivo de cena;
                float g = 1; // glossiness que vem do arquivo de cena
                // Point3D v = ray.getOrigin() - isect.p;
                // o h pode ser um l+v/||l+v|| esse valor de h é do material de selan
                Vec3 h = normalize(normalize(l) + normalize(-ray.getDirection())); // nao ta seguindo a recomendação de selan mas sim o material que ele passou referente ao blinnphong

                Vec3 n{ isect.n };  // Normal vector at the point where the ray hit the surface.
                float maxValue = max(0.f, dot(n, h));
                int k = 3; // quantidade de luzes presentes na cena;
                Vec3 result;
                
                for (int i = 0; i < k; i++){
                    result += kd * light_I * max( 0.f, dot( n, l )) + ks * light_I * pow(maxValue, g); // light_I é variável de acordo com a luz da vez entao tem que ser algo tipo lights[i].i
                }

                result = ka * light_IA + result; // coeficientee que ka vem do arquivo de cena assim como a luz ambiente
                Color new_color(result.r(), result.g(), result.b());
                // Determining pixel color based on Lambertian Shading only.
                L = new_color;
            }
            return L;
        }
};

#endif
