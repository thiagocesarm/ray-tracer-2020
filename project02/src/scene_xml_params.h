#ifndef _XML_PARAMS_
#define _XML_PARAMS_

namespace SceneTags {
    const string RT3 = "RT3";
    const string CAMERA = "camera";
    const string FILM = "film";
    const string WORLD_BEGIN = "world_begin";
    const string BACKGROUND = "background";
    const string WORLD_END = "world_end";
};

namespace CameraParams {
    const string TYPE = "type";
};

namespace FilmParams {
    const string TYPE = "type";
    const string X_RES = "x_res";
    const string Y_RES = "y_res";
    const string FILENAME = "filename";
    const string IMG_TYPE = "img_type";
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