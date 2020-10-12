#ifndef _API_
#define _API_

#include "../parser/paramset.h"
#include "../core/camera.h"
#include "../core/primitive.h"
#include "../primitives/geometric_primitive.h"
#include "../core/shape.h"
#include "../shapes/sphere.h"
#include "../cameras/orthographic.h"
#include "../cameras/perspective.h"
#include "../materials/flatMaterial.h"
#include "../core/film.h"
#include "../core/background.h"
#include "../parser/scene_xml_params.h"
#include "../core/rt3.h"
#include "../core/integrator.h"
#include "../core/material.h"
#include "../core/lookAt.h"
#include "../primitives/aggregate.h"
#include "../integrators/flat_integrator.h"

using namespace std;

struct RenderOptions {
    LookAt lookAt;
    Camera * camera;
    Film film;
    Background * background;
    Integrator * integrator;
    Material * material;
    vector<Primitive *> objects;
};

RenderOptions ro;

class API {
    private:
        static void finishCameraSetup();
    public:
        static void setLookAt(ParamSet & ps);
        static void setCamera(ParamSet & ps);
        static void setFilm(ParamSet & ps);
        static void setBackground(ParamSet & ps);
        static void setObject(ParamSet & ps);
        static void setMaterial(ParamSet & ps);
        static void setIntegrator(ParamSet & ps);
        static void setRayTracer(RT3 & rt3);
};

void API::setLookAt(ParamSet & ps) {
    auto lookAt = ps.findArray<int>(LookAtParams::LOOK_AT);
    auto lookFrom = ps.findArray<int>(LookAtParams::LOOK_FROM);
    auto up = ps.findArray<int>(LookAtParams::UP);

    ro.lookAt = LookAt(Point3D(lookFrom[0], lookFrom[1], lookFrom[2]),
                       Point3D(lookAt[0], lookAt[1], lookAt[2]), 
                       Vec3(up[0], up[1], up[2]));
}

void API::setCamera(ParamSet & ps) {
    auto type = ps.find<string>(CameraParams::TYPE, "");
    auto screen_window = ps.findArray<float>(CameraParams::SCREEN_WINDOW);
    auto fovy = ps.find<float>(CameraParams::FOVY, -1);

    if (type == CameraTypes::ORTHOGRAPHIC && screen_window != nullptr) { 
        ro.camera = new OrthographicCamera(screen_window[0], screen_window[1], screen_window[2], screen_window[3]);
        return;
    } else if (type == CameraTypes::PERSPECTIVE && fovy > -1) {
        ro.camera = new PerspectiveCamera(fovy);
        return;
    }
}

void API::setIntegrator(ParamSet & ps) {
    auto type = ps.find<string>(IntegratorParams::TYPE, IntegratorTypes::FLAT);

    if (type == IntegratorTypes::FLAT) {
        ro.integrator = new FlatIntegrator(ro.camera);
    }
}

void API::setFilm(ParamSet & ps) {
    auto type = ps.find<string>(FilmParams::TYPE, "image");
    auto xRes = ps.find<int>(FilmParams::X_RES, 800);
    auto yRes = ps.find<int>(FilmParams::Y_RES, 600);
    auto filename = ps.find<string>(FilmParams::FILENAME, "output_img.ppm");
    auto imgType = ps.find<string>(FilmParams::IMG_TYPE, "ppm");
    auto crop_window = ps.findArray<int>(FilmParams::CROP_WINDOW);
    int crop_window_vec[4];
    auto gamma_corrected = ps.find<string>(FilmParams::GAMMA_CORRECTED, "yes");
    
    if (crop_window != nullptr) {
        crop_window_vec[0] = crop_window[0];
        crop_window_vec[1] = crop_window[1];
        crop_window_vec[2] = crop_window[2];
        crop_window_vec[3] = crop_window[3];
        ro.film = Film(type, xRes, yRes, filename, imgType, crop_window_vec);
    } else {
        ro.film = Film(type, xRes, yRes, filename, imgType, nullptr);
    }

}

void API::setMaterial(ParamSet & ps) {
    auto type = ps.find<string>(MaterialParams::TYPE, MaterialTypes::FLAT);
    auto color = ps.findArray<float>(MaterialParams::COLOR);

    if (type == MaterialTypes::FLAT){
        ro.material = new FlatMaterial(Color(color[0],color[1],color[2]));
    }

}

void API::setObject(ParamSet & ps) {
    auto type = ps.find<string>(ObjectParams::TYPE, ObjectTypes::SPHERE);

    if (type == ObjectTypes::SPHERE) {
        auto radius = ps.find<float>(SphereParams::RADIUS, 0.4);
        auto center = ps.findArray<float>(SphereParams::CENTER);

        Shape * shape = new Sphere( radius, Point3D( center[0], center[1], center[2] ) );
        ro.objects.push_back( new GeometricPrimitive(shape, ro.material) );
    }
}

void API::setBackground(ParamSet & ps) {

    auto type = ps.find<string>(BackgroundParams::TYPE, "colors");
    auto color = ps.findArray<int>(BackgroundParams::COLOR);
    if (color != nullptr) {
        ro.background = new Background(Color(color[0], color[1], color[2]));
    } else {
        const int defaultColor[3] = { 0, 0, 0 };
        auto mapping = ps.find<string>(BackgroundParams::MAPPING, "screen");
        
        const int * blColors = ps.findArray<int>(BackgroundParams::BOTTOM_LEFT);
        if (blColors == nullptr) { blColors = defaultColor; }

        const int * tlColors = ps.findArray<int>(BackgroundParams::TOP_LEFT);
        if (tlColors == nullptr) { tlColors = defaultColor; }

        const int * trColors = ps.findArray<int>(BackgroundParams::TOP_RIGHT);
        if (trColors == nullptr) { trColors = defaultColor; }

        const int * brColors = ps.findArray<int>(BackgroundParams::BOTTOM_RIGHT);
        if (brColors == nullptr) { brColors = defaultColor; }

        ro.background = new Background(
            Color(blColors[0], blColors[1], blColors[2]),
            Color(tlColors[0], tlColors[1], tlColors[2]),
            Color(trColors[0], trColors[1], trColors[2]),
            Color(brColors[0], brColors[1], brColors[2])
        );
    }
}

void API::setRayTracer(RT3 & rt3) {
    finishCameraSetup();
    rt3.camera = ro.camera;
    rt3.integrator = ro.integrator;
    rt3.scene = new Scene( ro.background, shared_ptr<PrimList>( new PrimList(ro.objects) ) );
    // rt3.background = ro.background;
    // rt3.material = ro.material;
    // rt3.objects = ro.objects;
}

void API::finishCameraSetup() {
    ro.camera->film = &ro.film;
    ro.camera->finishSetup();
    ro.camera->build_camera_frame(ro.lookAt.lookFrom, ro.lookAt.lookAt, ro.lookAt.up);
}

#endif