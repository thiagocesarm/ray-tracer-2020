#ifndef _API_
#define _API_

#include "../cameras/orthographic.h"
#include "../cameras/perspective.h"
#include "../core/background.h"
#include "../core/camera.h"
#include "../core/film.h"
#include "../core/integrator.h"
#include "../core/lookAt.h"
#include "../core/material.h"
#include "../core/primitive.h"
#include "../core/rt3.h"
#include "../core/shape.h"
#include "../core/light.h"
#include "../materials/flatMaterial.h"
#include "../materials/blinn_phong_material.h"
#include "../integrators/flat_integrator.h"
#include "../integrators/blinn_phong_integrator.h"
#include "../parser/paramset.h"
#include "../parser/scene_xml_params.h"
#include "../primitives/aggregate.h"
#include "../primitives/geometric_primitive.h"
#include "../shapes/sphere.h"
#include "../shapes/triangle.h"
#include "../lights/ambient_light.h"
#include "../lights/directional_light.h"
#include "../lights/point_light.h"
#include "../lights/spot_light.h"

using namespace std;

struct RenderOptions {
    LookAt lookAt;
    Camera * camera;
    Film film;
    Background * background;
    vector<Light *> lights; 
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
        static void setLight(ParamSet & ps);
        static void setRayTracer(RT3 & rt3);
};

void API::setLookAt(ParamSet & ps) {
    auto lookAt = ps.findArray<float>(LookAtParams::LOOK_AT);
    auto lookFrom = ps.findArray<float>(LookAtParams::LOOK_FROM);
    auto up = ps.findArray<float>(LookAtParams::UP);

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

void API::setLight(ParamSet & ps) {
    auto type = ps.find<string>(LightSourceParams::TYPE, "");
    auto L = ps.findArray<float>(LightSourceParams::L);
    auto from = ps.findArray<float>(LightSourceParams::FROM);
    auto scale = ps.findArray<int>(LightSourceParams::SCALE);
    auto to = ps.findArray<float>(LightSourceParams::TO);
    auto I = ps.findArray<float>(LightSourceParams::I);
    auto cutoff = ps.find<float>(LightSourceParams::CUTOFF, 0.0);
    auto falloff = ps.find<float>(LightSourceParams::FALLOFF, 0.0);

    if (type == LightSourceTypesParams::AMBIENT && L != nullptr) {
        Vec3 vecL = Vec3(L[0], L[1], L[2]);
        AmbientLight *al = new AmbientLight(vecL);
        al->setType("ambient");
        al->setFrom(vecL);
        ro.lights.push_back(al);
        return;
    } else if (type == LightSourceTypesParams::DIRECTIONAL &&  L != nullptr && scale != nullptr && from != nullptr && to != nullptr) {
        Vec3 vecL = Vec3(L[0], L[1], L[2]);
        Vec3 vecScale = Vec3(scale[0], scale[1], scale[2]);
        Vec3 vecFrom = Vec3(from[0], from[1], from[2]);
        Vec3 vecTo = Vec3(to[0], to[1], to[2]);
        DirectionalLight *dl = new DirectionalLight(vecL, vecScale, vecFrom, vecTo);
        dl->setType("directional");
        dl->setFrom(vecFrom);
        ro.lights.push_back(dl);
        return;
    } else if (type == LightSourceTypesParams::POINT &&  I != nullptr && scale != nullptr && from != nullptr) {
        Vec3 vecI = Vec3(I[0], I[1], I[2]);
        Vec3 vecScale = Vec3(scale[0], scale[1], scale[2]);
        Vec3 vecFrom = Vec3(from[0], from[1], from[2]);
        PointLight *pl = new PointLight(vecI, vecScale, vecFrom);
        pl->setType("point");
        pl->setFrom(vecFrom);
        ro.lights.push_back(pl);
        return;
    } else if (type == LightSourceTypesParams::SPOT &&  I != nullptr && scale != nullptr && from != nullptr && to != nullptr) {
        Vec3 vecI = Vec3(I[0], I[1], I[2]);
        Vec3 vecScale = Vec3(scale[0], scale[1], scale[2]);
        Vec3 vecFrom = Vec3(from[0], from[1], from[2]);
        Vec3 vecTo = Vec3(to[0], to[1], to[2]);
        SpotLight *sl = new SpotLight(vecI, vecScale, vecFrom, vecTo, cutoff, falloff);
        sl->setType("spot");
        sl->setFrom(vecFrom);
        ro.lights.push_back(sl);
        return;
    }
}

void API::setIntegrator(ParamSet & ps) {
    auto type = ps.find<string>(IntegratorParams::TYPE, IntegratorTypes::FLAT);

    if (type == IntegratorTypes::FLAT) {
        ro.integrator = new FlatIntegrator(ro.camera);
    } else if (type == IntegratorTypes::BLINN) {
        auto depth = ps.find<int>(IntegratorParams::DEPTH, 0);
        ro.integrator = new BlinnPhongIntegrator(ro.camera, depth);
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
    auto type = ps.find<string>(MaterialParams::TYPE, "");

    if (type == MaterialTypes::FLAT) {
        auto color = ps.findArray<float>(FlatMaterialParams::COLOR);
        ro.material = new FlatMaterial(Color(color[0],color[1],color[2]));
    } else if (type == MaterialTypes::BLINN_PHONG) {
        auto ambient = ps.findArray<float>(BlinnPhongMaterialParams::AMBIENT);
        auto diffuse = ps.findArray<float>(BlinnPhongMaterialParams::DIFFUSE);
        auto specular = ps.findArray<float>(BlinnPhongMaterialParams::SPECULAR);
        auto mirror = ps.findArray<float>(BlinnPhongMaterialParams::MIRROR);
        auto glossiness = ps.find<int>(BlinnPhongMaterialParams::GLOSSINESS, 0);

        ro.material = new BlinnPhongMaterial (
            Vec3(ambient[0], ambient[1], ambient[2]),
            Vec3(diffuse[0], diffuse[1], diffuse[2]),
            Vec3(specular[0], specular[1], specular[2]),
            Vec3(mirror[0], mirror[1], mirror[2]),
            glossiness
        );
    }
}

void API::setObject(ParamSet & ps) {
    auto type = ps.find<string>(ObjectParams::TYPE, ObjectTypes::SPHERE);

    if (type == ObjectTypes::SPHERE) {
        auto radius = ps.find<float>(SphereParams::RADIUS, 0.4);
        auto center = ps.findArray<float>(SphereParams::CENTER);

        Shape * shape = new Sphere( radius, Point3D( center[0], center[1], center[2] ) );
        ro.objects.push_back( new GeometricPrimitive(shape, ro.material) );

    } else if (type == ObjectTypes::TRIANGLEMESH) {

        auto mesh = create_triangle_mesh_shape(false, ps);

        for (auto triangle : mesh) {
            ro.objects.push_back( new GeometricPrimitive(triangle.get(), ro.material) );
        }
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
    rt3.scene = new Scene( ro.background, shared_ptr<PrimList>( new PrimList(ro.objects) ), ro.lights, ro.objects );
}

void API::finishCameraSetup() {
    ro.camera->film = &ro.film;
    ro.camera->finishSetup();
    ro.camera->build_camera_frame(ro.lookAt.lookFrom, ro.lookAt.lookAt, ro.lookAt.up);
}

#endif