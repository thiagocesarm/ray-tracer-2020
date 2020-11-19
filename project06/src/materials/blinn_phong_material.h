#ifndef _BLINN_PHONG_MATERIAL_
#define _BLINN_PHONG_MATERIAL_

#include "../core/vec3.h"
#include "../core/material.h"

class BlinnPhongMaterial : public Material {
    public:
        Vec3 ambient;
        Vec3 diffuse;
        Vec3 specular;
        Vec3 mirror;
        int glossiness;

        BlinnPhongMaterial( 
            Vec3 mAmbient, 
            Vec3 mDiffuse, 
            Vec3 mSpecular, 
            Vec3 mMirror, 
            int mGlossiness
        ) {
            ambient = mAmbient;
            diffuse = mDiffuse;
            specular = mSpecular;
            mirror = mMirror;
            glossiness = mGlossiness;
        };

        void scatter( Surfel * isect, Ray * r ) override {
            /* TO DO */
        }
};

#endif