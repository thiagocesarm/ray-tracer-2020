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
            this->l = l; // Located at the base class.
            this->r = r; // Located at the base class.
            this->b = b; // Located at the base class.
            this->t = t; // Located at the base class.
        };

        void finishSetup() override { std::cout << ">>> Orthographic override!\n";  /* Empty */ }

        Ray generate_ray( int i, int j ) override {
            // The input coord, (x,y) are expressed in pixel coords, aka **Raster space**.
            // Calculate the normalivez value (u_int,v_int) correspoding to (x,y).
            float u_coord = l + ( r - l ) * ( i + 0.5f ) / film->getWidth();
            float v_coord = b + ( t - b ) * ( j + 0.5f ) / film->getHeight();
            // Determine the ray's origin (point on film) within this new UV coord. system. u_int,v_int in [0,1].
            Ray r = Ray(eye + u_coord * u + v_coord * v, view_plane_normal);
            return r;
        }
};


#endif