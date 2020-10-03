#ifndef _API_
#define _API_

#include "paramset.h"
#include "camera.h"
#include "film.h"
#include "background.h"
#include "scene_xml_params.h"
#include "rt3.h"

using namespace std;

struct RenderOptions {
    Camera camera;
    Film film;
    Background background;
};

RenderOptions ro;

class API {
    public:
        static void setCamera(ParamSet & ps);
        static void setFilm(ParamSet & ps);
        static void setBackground(ParamSet & ps);
        static void setRayTracer(RT3 & rt3);
};

void API::setCamera(ParamSet & ps) {
    auto type = ps.find<string>(CameraParams::TYPE, "orthographic");

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