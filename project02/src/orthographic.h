#ifndef ORTHO_H
#define ORTHO_H

#include "film.h"
#include "camera.h"
#include "point3D.h"
#include "vec3.h"
#include "ray.h"


class OrthographicCamera : public Camera {
    public:
        void set_parallel_box( float l, float r, float b, float t){
            /*
         * === SETTING THE IMAGE PLANE ===
         *
         * For the orthographic projetion we need to determine the
         * view plane's dimensions based on the 4 values passed in.
         * The view plane may have a normal different from -w.
         * By default, the focal plane is always located at the
         * camera's orgin (m_eye). In fact, it does not matter
         * where the view plane is located, since the rays are
         * parallel.
         *
         */
        // Save view plane normal.
            this->l = l;
            this->r = r;
            this->b = b;
            this->t = t;
            vpn = w ;

        // TODO
        }
        OrthographicCamera(
                        Point3D lfrom=Point3D{0,0,0},
                        Point3D lat=Point3D{0,0,-1},
                        Vec3 vup=Vec3{0,1,0},
                        float l=0, float r=0, float b=0, float t=0,
                        Film * film=nullptr
                        )
                    : Camera(film) {
                        this->l = l; // Located at the base class.
                        this->r = r;
                        this->b = b;
                        this->t = t;
                        build_camera_frame( lfrom, lat, vup );
                        set_parallel_box( l, r, b, t );
                    };
        
        void OrthographicCamera::generate_ray( int x, int y, Ray& ray ) const {
        // The input coord, (x,y) are expressed in pixel coords, aka **Raster space**.
        // Calculate the normalivez value (u_int,v_int) correspoding to (x,y).
        float u_int = l + (r-l)*(x+0.5f)/film->getWidth();
        float v_int = b + (t-b)*(y+0.5)/film->getHeight();
        // Determine the ray's origin (point on film) within this new UV coord. system. u_int,v_int in [0,1].
        ray.setOrigin(eye + u_int*u + v_int*v);
        // All rays have the same direction.
        ray.setDirection(normalize(vpn));
        }

    };


#endif