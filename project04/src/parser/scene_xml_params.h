#ifndef _XML_PARAMS_
#define _XML_PARAMS_

namespace SceneTags {
    const string RT3 = "RT3";
    const string CAMERA = "camera";
    const string FILM = "film";
    const string WORLD_BEGIN = "world_begin";
    const string BACKGROUND = "background";
    const string WORLD_END = "world_end";
    const string LOOK_AT = "lookat";
    const string INTEGRATOR = "integrator";
    const string MATERIAL = "material";
    const string OBJECT = "object";
};

namespace IntegratorParams {
    const string TYPE = "type";
};

namespace IntegratorTypes {
    const string FLAT = "flat";
};

namespace MaterialParams {
    const string TYPE = "type";
    const string COLOR = "color";
};

namespace MaterialTypes {
    const string FLAT = "flat";
};

namespace ObjectParams {
    const string TYPE = "type";
};

namespace ObjectTypes {
    const string SPHERE = "sphere";
}

namespace SphereParams {
    const string RADIUS = "radius";
    const string CENTER = "center";
}

namespace CameraParams {
    const string TYPE = "type";
    const string SCREEN_WINDOW = "screen_window";
    const string FOVY = "fovy";
};

namespace CameraTypes {
    const string ORTHOGRAPHIC = "orthographic";
    const string PERSPECTIVE = "perspective";
}

namespace LookAtParams {
    const string LOOK_FROM = "look_from";
    const string LOOK_AT = "look_at";
    const string UP = "up";
};

namespace FilmParams {
    const string TYPE = "type";
    const string X_RES = "x_res";
    const string Y_RES = "y_res";
    const string FILENAME = "filename";
    const string IMG_TYPE = "img_type";
    const string CROP_WINDOW = "crop_window";
    const string GAMMA_CORRECTED = "gamma_corrected";
};

namespace BackgroundParams {
    const string TYPE = "type";
    const string COLOR = "color";
    const string MAPPING = "mapping";
    const string BOTTOM_LEFT = "bl";
    const string TOP_LEFT = "tl";
    const string TOP_RIGHT = "tr";
    const string BOTTOM_RIGHT = "br";
};

#endif