#ifndef _PERSP_CAM_
#define _PERSP_CAM_

#define PI 3.14159265358979323846

#include "../core/film.h"
#include "../core/camera.h"
#include "../core/point3D.h"
#include "../core/vec3.h"
#include "../core/ray.h"

class PerspectiveCamera : public Camera {
    public:
        float fovy;
        float focal_distance;

        PerspectiveCamera(
            float fovy
        ) {
            this->type = CameraTypes::PERSPECTIVE;
            this->fovy = fovy;
            this->focal_distance = 1.0; // TODO: Get it as scene parameter
        }

        void finishSetup() override {
            // Calculate screen dimensions based on fovy and image dimensions
            float aspect_ratio = float(film->getWidth()) / float(film->getHeight());
            float fovy_radians = fovy * PI / 180;
            float h = tan(fovy_radians / 2) * focal_distance; // focal_distance will always be 1 for now
            this->b = -h;
            this->t = h;
            this->l = aspect_ratio * -h;
            this->r = aspect_ratio * h;
        }

        Ray generate_ray( int i, int j ) override {
            float u_coord = l + ( r - l ) * ( i + 0.5f ) / film->getWidth();
            float v_coord = b + ( t - b ) * ( j + 0.5f ) / film->getHeight();

            Ray r = Ray(eye, focal_distance * w + u_coord * u + v_coord * v);
            return r;
        }
};

#endif