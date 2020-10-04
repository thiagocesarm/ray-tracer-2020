#ifndef PERSP_H
#define PERSP

#define PI 3.14159265358979323846

#include "film.h"
#include "camera.h"
#include "point3D.h"
#include "vec3.h"
#include "ray.h"


class PerspectiveCamera : public Camera {
    private:
        float fovy;
        void setScreenWindow(int width, int height) {
            float aspect_ratio = float(width) / float(height);
            float fovy_radians = fovy * PI / 180;
            float h = tan(fovy_radians / 2);
            this->b = -h;
            this->t = h;
            this->l = aspect_ratio * -h;
            this->r = aspect_ratio * h;
        }

    public:
        PerspectiveCamera(
            Point3D look_from,
            Point3D look_at,
            Vec3 vup,
            float fovy,
            Film * film
        ) : Camera(film) {
            build_camera_frame(look_from, look_at, vup);
            this->fovy = fovy;
            this->film = film;
            setScreenWindow(film->getWidth(), film->getHeight());
        }

        Ray generate_ray( int x, int y, int width, int height) const {
            float u_int = l + (r-l)*(x+0.5f)/width;
            float v_int = b + (t-b)*(y+0.5f)/height;
            float focal_distance = 1; // TODO: Make it a class property

            Ray r = Ray(eye, focal_distance * w + u_int * u + v_int * v);
            return r;
        }
};

#endif