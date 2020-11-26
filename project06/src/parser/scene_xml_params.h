#ifndef _XML_PARAMS_
#define _XML_PARAMS_

namespace SceneTags {
    const string RT3 = "RT3";
    const string CAMERA = "camera";
    const string FILM = "film";
    const string WORLD_BEGIN = "world_begin";
    const string BACKGROUND = "background";
    const string LIGHT_SOURCE = "light_source";
    const string WORLD_END = "world_end";
    const string LOOK_AT = "lookat";
    const string INTEGRATOR = "integrator";
    const string MATERIAL = "material";
    const string OBJECT = "object";
};

namespace IntegratorParams {
    const string TYPE = "type";
    const string DEPTH = "depth";
};

namespace IntegratorTypes {
    const string FLAT = "flat";
    const string BLINN = "blinn_phong";
};

namespace LightSourceParams {
    const string TYPE = "type";
    const string L = "L";
    const string SCALE = "scale";
    const string FROM = "from";
    const string TO = "to";
    const string I = "I";
    const string CUTOFF = "cutoff";
    const string FALLOFF = "falloff";

};

namespace LightSourceTypesParams {
    const string AMBIENT = "ambient";
    const string DIRECTIONAL = "directional";
    const string POINT = "point";
    const string SPOT = "spot";
};

namespace MaterialParams {
    const string TYPE = "type";
};

namespace FlatMaterialParams {
    const string COLOR = "color";
};

namespace BlinnPhongMaterialParams {
    const string AMBIENT = "ambient";
    const string DIFFUSE = "diffuse";
    const string SPECULAR = "specular";
    const string MIRROR = "mirror";
    const string GLOSSINESS = "glossiness";
};

namespace MaterialTypes {
    const string FLAT = "flat";
    const string BLINN_PHONG = "blinn";
};

namespace ObjectParams {
    const string TYPE = "type";
};

namespace ObjectTypes {
    const string SPHERE = "sphere";
    const string TRIANGLEMESH = "triangleMesh";
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

namespace TriangleParams {
    const string TYPE = "type";
    const string MATERIAL = "material";
    const string NTRIANGLES = "ntriangles";
    const string INDICES = "indices";
    const string VERTICES = "vertices";
    const string NORMALS = "normals";
    const string UVs = "uvs";
    const string REVERSE_VERTEX_ORDER = "reverse_vertex_order";
    const string COMPUTE_NORMALS = "compute_normals";
    const string BACKFACE_CULL = "backface_cull";
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