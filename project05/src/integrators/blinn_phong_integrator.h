#ifndef _BLINN_PHONG_INTEGRATOR_
#define _BLINN_PHONG_INTEGRATOR_

#include <iostream>
#include "../core/integrator.h"
#include "../core/light.h"
#include "../lights/ambient_light.h"
#include "../materials/blinn_phong_material.h"

class BlinnPhongIntegrator: public SamplerIntegrator {
    private:
        int max_depth;
        float reflected_ray_offset = 0.01;
    public:
        BlinnPhongIntegrator(Camera * cam, int mDepth) : SamplerIntegrator(cam), max_depth{ mDepth } { }

        Color Li(const Ray& ray, const Scene & scene, const Color bkg_color ) const override {
            Color L(0,0,0);
            Surfel isect; // Intersection information.  
            L = Li_depth(ray, scene, bkg_color, isect, 0);
            
            // Check for RGB "overflow"
            float r = L.r() > 1 ? 1 : L.r();
            float g = L.g() > 1 ? 1 : L.g();
            float b = L.b() > 1 ? 1 : L.b();
            return Color(r, g, b);
        }

        Color Li_depth(const Ray& ray, const Scene & scene, const Color bkg_color, Surfel& isect, int depth ) const {
            if (!scene.intersect(ray, &isect)) {
                return bkg_color;
            } else {
                BlinnPhongMaterial *bpMaterial = dynamic_cast< BlinnPhongMaterial *>( isect.primitive->getMaterial() );
                auto km = bpMaterial->mirror;
                auto ka = bpMaterial->ambient;
                auto kd = bpMaterial->diffuse;
                auto ks = bpMaterial->specular;
                auto glossiness = bpMaterial->glossiness;
                auto vecN = isect.n;

                Vec3 ambientLight = Vec3(0, 0, 0);
                Vec3 result = Vec3(0, 0, 0);
                Vec3 vecP = Vec3{isect.p.getX(), isect.p.getY(), isect.p.getZ()};

                for(auto & light : scene.lights) { 
                    if (light->getType() == light_type_e::ambient) {
                        light->sample_Li(isect, &ambientLight);
                        continue;
                    }
                    Vec3 I = Vec3();
                    auto color = light->sample_Li(isect, &I); // updates I according to current light
                    auto vecL = Vec3(color.r(), color.g(), color.b());
                    if (light->getTypeString() == "directional") {
                        Vec3 vecDirecton = light->getFrom() - vecP;
                        Ray shadow_ray{isect.p, vecDirecton};
                        for(auto & object : scene.objects) {
                            if (!object->intersect_p(shadow_ray)) {
                                Vec3 vecH = normalize( vecL + normalize( -ray.getDirection() ) ); // nao ta seguindo a recomendação de selan mas sim o material que ele passou referente ao blinnphong
                                float maxValue = max(0.f, dot(vecN, vecH));
                                result += kd * I * max( 0.f, dot( vecN, vecL )) + ks * I * pow(maxValue, glossiness); // light_I é variável de acordo com a luz da vez entao tem que ser algo tipo lights[i].i
                
                            }
                        }
                    } else {
                        Vec3 vecDirecton = normalize(light->getFrom() - vecP);
                        Ray shadow_ray{isect.p, vecDirecton, 0.0, 1.0};
                        for(auto & object : scene.objects) {               
                            if (!object->intersect_p(shadow_ray)) {
                                Vec3 vecH = normalize( vecL + normalize( -ray.getDirection() ) ); // nao ta seguindo a recomendação de selan mas sim o material que ele passou referente ao blinnphong
                                float maxValue = max(0.f, dot(vecN, vecH));
                                result += (kd * I * max( 0.f, dot( vecN, vecL )) + ks * I * pow(maxValue, glossiness)) / (scene.objects.size()); // light_I é variável de acordo com a luz da vez entao tem que ser algo tipo lights[i].i                         
                            } 
                                
                       }
                    }
                }
                // Ambient contribution
                result = ka * ambientLight + result;
            
                float r = result.r();
                float g = result.g();
                float b = result.b();

                // Mirror reflection
                if (depth < max_depth && !km.is_neutral()) {
                    // Reflected ray's origin is surfel's hit point
                    Ray reflected_ray = Ray(isect.p, ray.getDirection() - 2 * (dot(ray.getDirection(), vecN)) * vecN); // vecN = isect's normal
                    reflected_ray.setOrigin(reflected_ray(reflected_ray_offset));

                    // Background color for next Li_depth call is current result color
                    auto mirror_color = Li_depth(reflected_ray, scene, Color(r, g, b), isect, depth + 1);
                    auto new_color_vec = Vec3(r, g, b) + km * Vec3(mirror_color.r(), mirror_color.g(), mirror_color.b());

                    r = new_color_vec.r();
                    g = new_color_vec.g();
                    b = new_color_vec.b();
                }

                return Color(r, g, b);
            }
        }
};

#endif