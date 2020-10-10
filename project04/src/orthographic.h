#ifndef _ORTHO_CAM_
#define _ORTHO_CAM_

#include "film.h"
#include "camera.h"
#include "point3D.h"
#include "vec3.h"
#include "ray.h"


class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(
            float l, 
            float r, 
            float b, 
            float t
        ) {
            this->type = CameraTypes::ORTHOGRAPHIC;
            this->l = l;
            this->r = r;
            this->b = b;
            this->t = t;
        };

        void finishSetup() override { /* Empty */ }

        Ray generate_ray( int i, int j ) override {
            float u_coord = l + ( r - l ) * ( i + 0.5f ) / film->getWidth();
            float v_coord = b + ( t - b ) * ( j + 0.5f ) / film->getHeight();
            Ray r = Ray(eye + u_coord * u + v_coord * v, w );
            return r;
        }
};


#endif