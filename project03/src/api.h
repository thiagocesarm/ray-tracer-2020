#ifndef _API_
#define _API_

#include "paramset.h"
#include "camera.h"
#include "film.h"
#include "background.h"
#include "scene_xml_params.h"
#include "rt3.h"
#include "integrator.h"
#include "material.h"
#include "object.h"
#include "lookAt.h"

using namespace std;

struct RenderOptions {
    Camera camera;
    Film film;
    Background background;
    Integrator integrator;
    Material material;
    vector<Object> objects;
    LookAt lookAt;
};

RenderOptions ro;

class API {
    public:
        static void setCamera(ParamSet & ps);
        static void setFilm(ParamSet & ps);
        static void setBackground(ParamSet & ps);
        static void setObject(ParamSet & ps);
        static void setMaterial(ParamSet & ps);
        static void setIntegrator(ParamSet & ps);
        static void setLookAt(ParamSet & ps);
        static void setRayTracer(RT3 & rt3);
};

void API::setCamera(ParamSet & ps) {
    auto type = ps.find<string>(CameraParams::TYPE, "orthographic");

    ro.integrator = Integrator(type);
}

void API::setIntegrator(ParamSet & ps) {
    auto type = ps.find<string>(IntegratorParams::TYPE, "flat");

    ro.camera = Camera(type);
}

void API::setFilm(ParamSet & ps) {
    auto type = ps.find<string>(FilmParams::TYPE, "image");
    auto xRes = ps.find<int>(FilmParams::X_RES, 800);
    auto yRes = ps.find<int>(FilmParams::Y_RES, 600);
    auto filename = ps.find<string>(FilmParams::FILENAME, "output_img.ppm");
    auto imgType = ps.find<string>(FilmParams::IMG_TYPE, "ppm");

    ro.film = Film(type, xRes, yRes, filename, imgType);
}

void API::setMaterial(ParamSet & ps) {
    auto type = ps.find<string>(MaterialParams::TYPE, "flat");
    auto color = ps.findArray<float>(MaterialParams::COLOR);

    ro.material = Material(type, Color(color[0],color[1],color[2]));
}

void API::setObject(ParamSet & ps) {
    auto type = ps.find<string>(ObjectParams::TYPE, "sphere");
    auto radius = ps.find<float>(ObjectParams::RADIUS, 0.4);
    auto center = ps.findArray<float>(ObjectParams::CENTER);

    ro.objects.push_back(Object(type, radius, Point3D(center[0],center[1],center[2])));
}

void API::setLookAt(ParamSet & ps) {
    auto lookAt = ps.findArray<int>(LookAtParams::LOOK_AT);
    auto lookFrom = ps.findArray<int>(LookAtParams::LOOK_FROM);
    auto up = ps.findArray<int>(LookAtParams::UP);

    ro.lookAt = LookAt(Point3D(lookAt[0], lookAt[1], lookAt[2]), 
                       Point3D(lookFrom[0], lookFrom[1], lookFrom[2]),
                       Point3D(up[0],up[1],up[2]));
}

void API::setBackground(ParamSet & ps) {

    auto type = ps.find<string>(BackgroundParams::TYPE, "colors");
    auto color = ps.findArray<int>(BackgroundParams::COLOR);
    if (color != nullptr) {
        ro.background = Background(Color(color[0], color[1], color[2]));
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

        ro.background = Background(
            Color(blColors[0], blColors[1], blColors[2]),
            Color(tlColors[0], tlColors[1], tlColors[2]),
            Color(trColors[0], trColors[1], trColors[2]),
            Color(brColors[0], brColors[1], brColors[2])
        );
    }
}

void API::setRayTracer(RT3 & rt3) {
    rt3.camera = ro.camera;
    rt3.film = move(ro.film);
    rt3.background = ro.background;
}

#endif