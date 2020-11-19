#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <sstream>
#include "../ext/tinyxml2.h"
#include "../parser/paramset.h"
#include "../parser/scene_xml_params.h"
#include "../core/api.h"
#include "../core/rt3.h"
#include "../core/light.h"
#include "../lights/ambient_light.h"
#include "../lights/directional_light.h"
#include "../lights/spot_light.h"
#include "../lights/point_light.h"

using namespace std;
using namespace tinyxml2;

class Parser {
    private:
        const string sceneFile;
        void processTag(XMLElement * currentNode);
        template <typename T> void fillArrayWithValuesFromString(string mString, unique_ptr<T[]> & array, size_t size);
    public:
        Parser(string mSceneFile) : sceneFile(mSceneFile) {}
        bool parseSceneFile();
        void loadScene(RT3 & rayTracer);
};

bool Parser::parseSceneFile() {
    XMLDocument doc;
    if (doc.LoadFile(sceneFile.c_str()) != XML_SUCCESS){
        std::cout << ">>> Unable to open scene description file!" << std::endl;
        return false;
    }

    XMLPrinter printer;
    doc.Print(&printer);

    processTag(doc.FirstChildElement());
    return true;
}

void Parser::processTag(XMLElement * currentNode) {
    if (currentNode == nullptr) {
        return;
    }

    string tag = currentNode->Value();
    unique_ptr<ParamSet> currentParamSet{ new ParamSet() };

    if (tag == SceneTags::CAMERA) {
        unique_ptr<string[]> type{ new string[1] };
        type[0] = currentNode->Attribute(CameraParams::TYPE.c_str());
        currentParamSet->add<string>(CameraParams::TYPE, move(type), 1);

        if (currentNode->Attribute(CameraParams::SCREEN_WINDOW.c_str()) != nullptr) {
            string screen_WindowString = currentNode->Attribute(CameraParams::SCREEN_WINDOW.c_str());
            unique_ptr<float[]> sreen_windowArray{ new float[4] };
            fillArrayWithValuesFromString<float>(screen_WindowString, sreen_windowArray, 4);
            currentParamSet->add<float>(CameraParams::SCREEN_WINDOW, move(sreen_windowArray), 4);
        }

        if (currentNode->Attribute(CameraParams::FOVY.c_str()) != nullptr) {
            unique_ptr<float[]> fovy{ new float[1] };
            fovy[0] = currentNode->FloatAttribute(CameraParams::FOVY.c_str());
            currentParamSet->add<float>(CameraParams::FOVY, move(fovy), 1);
        }

        API::setCamera(*currentParamSet);
    } else if (tag == SceneTags::LIGHT_SOURCE) {
        unique_ptr<string[]> type{ new string[1] };
        type[0] = currentNode->Attribute(LightSourceParams::TYPE.c_str());
        currentParamSet->add<string>(LightSourceParams::TYPE, move(type), 1);

        if (currentNode->Attribute(LightSourceParams::L.c_str()) != nullptr) {
            string LString = currentNode->Attribute(LightSourceParams::L.c_str());
            unique_ptr<float[]> LArray{ new float[3] };
            fillArrayWithValuesFromString<float>(LString, LArray, 3);
            currentParamSet->add<float>(LightSourceParams::L, move(LArray), 3);
        }

        if (currentNode->Attribute(LightSourceParams::SCALE.c_str()) != nullptr) {
            string ScaleString = currentNode->Attribute(LightSourceParams::SCALE.c_str());
            unique_ptr<int[]> ScaleArray{ new int[3] };
            fillArrayWithValuesFromString<int>(ScaleString, ScaleArray, 3);
            currentParamSet->add<int>(LightSourceParams::SCALE, move(ScaleArray), 3);
        }

        if (currentNode->Attribute(LightSourceParams::FROM.c_str()) != nullptr) {
            string FromString = currentNode->Attribute(LightSourceParams::FROM.c_str());
            unique_ptr<float[]> FromArray{ new float[3] };
            fillArrayWithValuesFromString<float>(FromString, FromArray, 3);
            currentParamSet->add<float>(LightSourceParams::FROM, move(FromArray), 3);
        }

        if (currentNode->Attribute(LightSourceParams::TO.c_str()) != nullptr) {
            string ToString = currentNode->Attribute(LightSourceParams::TO.c_str());
            unique_ptr<float[]> ToArray{ new float[3] };
            fillArrayWithValuesFromString<float>(ToString, ToArray, 3);
            currentParamSet->add<float>(LightSourceParams::TO, move(ToArray), 3);
        }

        if (currentNode->Attribute(LightSourceParams::I.c_str()) != nullptr) {
            string IString = currentNode->Attribute(LightSourceParams::I.c_str());
            unique_ptr<float[]> IArray{ new float[3] };
            fillArrayWithValuesFromString<float>(IString, IArray, 3);
            currentParamSet->add<float>(LightSourceParams::I, move(IArray), 3);
        }

        if (currentNode->Attribute(LightSourceParams::CUTOFF.c_str()) != nullptr) {
            unique_ptr<float[]> cutoff{ new float[1] };
            cutoff[0] = currentNode->FloatAttribute(LightSourceParams::CUTOFF.c_str());
            currentParamSet->add<float>(LightSourceParams::CUTOFF, move(cutoff), 1);
        }

        if (currentNode->Attribute(LightSourceParams::FALLOFF.c_str()) != nullptr) {
            unique_ptr<float[]> falloff{ new float[1] };
            falloff[0] = currentNode->FloatAttribute(LightSourceParams::FALLOFF.c_str());
            currentParamSet->add<float>(LightSourceParams::FALLOFF, move(falloff), 1);
        }
        API::setLight(*currentParamSet);
    } else if (tag == SceneTags::FILM) {
        unique_ptr<string[]> type{ new string[1] };
        type[0] = currentNode->Attribute(FilmParams::TYPE.c_str());
        currentParamSet->add<string>(FilmParams::TYPE, move(type), 1);

        unique_ptr<int[]> xResolution{ new int[1] };
        xResolution[0] = currentNode->IntAttribute(FilmParams::X_RES.c_str());
        currentParamSet->add<int>(FilmParams::X_RES, move(xResolution), 1);

        unique_ptr<int[]> yResolution{ new int[1] };
        yResolution[0] = currentNode->IntAttribute(FilmParams::Y_RES.c_str());
        currentParamSet->add<int>(FilmParams::Y_RES, move(yResolution), 1);

        unique_ptr<string[]> filename{ new string[1] };
        filename[0] = currentNode->Attribute(FilmParams::FILENAME.c_str());
        currentParamSet->add<string>(FilmParams::FILENAME, move(filename), 1);

        unique_ptr<string[]> imageType{ new string[1] };
        imageType[0] = currentNode->Attribute(FilmParams::IMG_TYPE.c_str());
        currentParamSet->add<string>(FilmParams::IMG_TYPE, move(imageType), 1);

        if (currentNode->Attribute(FilmParams::CROP_WINDOW.c_str()) != nullptr) {
            string crop_WindowString = currentNode->Attribute(FilmParams::CROP_WINDOW.c_str());
            unique_ptr<int[]> crop_windowArray{ new int[4] };
            fillArrayWithValuesFromString<int>(crop_WindowString, crop_windowArray, 4);
            currentParamSet->add<int>(FilmParams::CROP_WINDOW, move(crop_windowArray), 4);
        }

        if (currentNode->Attribute(FilmParams::GAMMA_CORRECTED.c_str()) != nullptr) {
            unique_ptr<string[]> gamma_corrected{ new string[1] };
            gamma_corrected[0] = currentNode->Attribute(FilmParams::GAMMA_CORRECTED.c_str());
            currentParamSet->add<string>(FilmParams::GAMMA_CORRECTED, move(gamma_corrected), 1);
        }
        
        API::setFilm(*currentParamSet);
    } else if (tag == SceneTags::BACKGROUND) {
        unique_ptr<string[]> type{ new string[1] };
        type[0] = currentNode->Attribute(BackgroundParams::TYPE.c_str());
        currentParamSet->add<string>(BackgroundParams::TYPE, move(type), 1);

        if (currentNode->Attribute(BackgroundParams::COLOR.c_str()) != nullptr) {
            string colorValuesString = currentNode->Attribute(BackgroundParams::COLOR.c_str());
            unique_ptr<int[]> colorArray( new int[3] );
            fillArrayWithValuesFromString<int>(colorValuesString, colorArray, 3);
            currentParamSet->add<int>(BackgroundParams::COLOR, move(colorArray), 3);
        }

        if (currentNode->Attribute(BackgroundParams::MAPPING.c_str())) {
            unique_ptr<string[]> mapping{ new string[1] };
            mapping[0] = currentNode->Attribute(BackgroundParams::MAPPING.c_str());
            currentParamSet->add<string>(BackgroundParams::MAPPING, move(mapping), 1);
        }

        if (currentNode->Attribute(BackgroundParams::BOTTOM_LEFT.c_str())) {
            string bottomLeftColorsString = currentNode->Attribute(BackgroundParams::BOTTOM_LEFT.c_str());
            unique_ptr<int[]> bottomLeftColorsArray( new int[3] );
            fillArrayWithValuesFromString<int>(bottomLeftColorsString, bottomLeftColorsArray, 3);
            currentParamSet->add<int>(BackgroundParams::BOTTOM_LEFT, move(bottomLeftColorsArray), 3);
        }

        if (currentNode->Attribute(BackgroundParams::TOP_LEFT.c_str())) {
            string topLeftColorsString = currentNode->Attribute(BackgroundParams::TOP_LEFT.c_str());
            unique_ptr<int[]> topLeftColorsArray( new int[3] );
            fillArrayWithValuesFromString<int>(topLeftColorsString, topLeftColorsArray, 3);
            currentParamSet->add<int>(BackgroundParams::TOP_LEFT, move(topLeftColorsArray), 3);
        }

        if (currentNode->Attribute(BackgroundParams::TOP_RIGHT.c_str())) {
            string topRightColorsString = currentNode->Attribute(BackgroundParams::TOP_RIGHT.c_str());
            unique_ptr<int[]> topRightColorsArray( new int[3] );
            fillArrayWithValuesFromString<int>(topRightColorsString, topRightColorsArray, 3);
            currentParamSet->add<int>(BackgroundParams::TOP_RIGHT, move(topRightColorsArray), 3);
        }

        if (currentNode->Attribute(BackgroundParams::BOTTOM_RIGHT.c_str())) {
            string bottomRightColorsString = currentNode->Attribute(BackgroundParams::BOTTOM_RIGHT.c_str());
            unique_ptr<int[]> bottomRightColorsArray( new int[3] );
            fillArrayWithValuesFromString<int>(bottomRightColorsString, bottomRightColorsArray, 3);
            currentParamSet->add<int>(BackgroundParams::BOTTOM_RIGHT, move(bottomRightColorsArray), 3);
        }

        API::setBackground(*currentParamSet);
    } else if (tag == SceneTags::INTEGRATOR) {
        unique_ptr<string[]> type{ new string[1] };
        type[0] = currentNode->Attribute(IntegratorParams::TYPE.c_str());
        currentParamSet->add<string>(IntegratorParams::TYPE, move(type), 1);

        unique_ptr<int[]> depth{ new int[1] };
        depth[0] = currentNode->FloatAttribute(IntegratorParams::DEPTH.c_str());
        currentParamSet->add<int>(IntegratorParams::DEPTH, move(depth), 1);

        API::setIntegrator(*currentParamSet);
    } else if (tag == SceneTags::MATERIAL) {
        unique_ptr<string[]> type{ new string[1] };
        type[0] = currentNode->Attribute(MaterialParams::TYPE.c_str());
        string materialType = type.get()[0];
        currentParamSet->add<string>(MaterialParams::TYPE, move(type), 1);

        if (materialType == MaterialTypes::FLAT) {
            string colorsString = currentNode->Attribute(FlatMaterialParams::COLOR.c_str());
            unique_ptr<float[]> colorsArray( new float[3] );
            fillArrayWithValuesFromString<float>(colorsString, colorsArray, 3);
            currentParamSet->add<float>(FlatMaterialParams::COLOR, move(colorsArray), 3);
        } else if (materialType == MaterialTypes::BLINN_PHONG) {
            string ambientSring = currentNode->Attribute(BlinnPhongMaterialParams::AMBIENT.c_str());
            unique_ptr<float[]> ambientArray( new float[3] );
            fillArrayWithValuesFromString<float>(ambientSring, ambientArray, 3);
            currentParamSet->add<float>(BlinnPhongMaterialParams::AMBIENT, move(ambientArray), 3);

            string diffuseSring = currentNode->Attribute(BlinnPhongMaterialParams::DIFFUSE.c_str());
            unique_ptr<float[]> diffuseArray( new float[3] );
            fillArrayWithValuesFromString<float>(diffuseSring, diffuseArray, 3);
            currentParamSet->add<float>(BlinnPhongMaterialParams::DIFFUSE, move(diffuseArray), 3);

            string specularSring = currentNode->Attribute(BlinnPhongMaterialParams::SPECULAR.c_str());
            unique_ptr<float[]> specularArray( new float[3] );
            fillArrayWithValuesFromString<float>(specularSring, specularArray, 3);
            currentParamSet->add<float>(BlinnPhongMaterialParams::SPECULAR, move(specularArray), 3);

            string mirrorSring = currentNode->Attribute(BlinnPhongMaterialParams::MIRROR.c_str());
            unique_ptr<float[]> mirrorArray( new float[3] );
            fillArrayWithValuesFromString<float>(mirrorSring, mirrorArray, 3);
            currentParamSet->add<float>(BlinnPhongMaterialParams::MIRROR, move(mirrorArray), 3);

            unique_ptr<int[]> glossines{ new int[1] };
            glossines[0] = currentNode->IntAttribute(BlinnPhongMaterialParams::GLOSSINESS.c_str());
            currentParamSet->add<int>(BlinnPhongMaterialParams::GLOSSINESS, move(glossines), 1);
        }

        
        API::setMaterial(*currentParamSet);
    } else if (tag == SceneTags::OBJECT) {
        unique_ptr<string[]> type{ new string[1] };
        type[0] = currentNode->Attribute(ObjectParams::TYPE.c_str());
        string objectType = type[0];
        currentParamSet->add<string>(ObjectParams::TYPE, move(type), 1);

        if (objectType == ObjectTypes::SPHERE) {
            unique_ptr<float[]> radius{ new float[1] };
            radius[0] = currentNode->FloatAttribute(SphereParams::RADIUS.c_str());
            currentParamSet->add<float>(SphereParams::RADIUS, move(radius), 1);
            
            string centerString = currentNode->Attribute(SphereParams::CENTER.c_str());
            unique_ptr<float[]> centerArray( new float[3] );
            fillArrayWithValuesFromString<float>(centerString, centerArray, 3);
            currentParamSet->add<float>(SphereParams::CENTER, move(centerArray), 3);
        }
        
        API::setObject(*currentParamSet);
    } else if (tag == SceneTags::LOOK_AT) {
        string lookAtString = currentNode->Attribute(LookAtParams::LOOK_AT.c_str());
        unique_ptr<float[]> lookAtArray( new float[3] );
        fillArrayWithValuesFromString<float>(lookAtString, lookAtArray, 3);
        currentParamSet->add<float>(LookAtParams::LOOK_AT, move(lookAtArray), 3);

        string lookFromString = currentNode->Attribute(LookAtParams::LOOK_FROM.c_str());
        unique_ptr<float[]> lookFromArray( new float[3] );
        fillArrayWithValuesFromString<float>(lookFromString, lookFromArray, 3);
        currentParamSet->add<float>(LookAtParams::LOOK_FROM, move(lookFromArray), 3);

        string upString = currentNode->Attribute(LookAtParams::UP.c_str());
        unique_ptr<float[]> upArray( new float[3] );
        fillArrayWithValuesFromString<float>(upString, upArray, 3);
        currentParamSet->add<float>(LookAtParams::UP, move(upArray), 3);
        
        API::setLookAt(*currentParamSet);
    }
    processTag(currentNode->FirstChildElement());
    processTag(currentNode->NextSiblingElement());
}

void Parser::loadScene(RT3 & rayTracer) {
    API::setRayTracer(rayTracer);
}

template <typename T>
void Parser::fillArrayWithValuesFromString(string mString, unique_ptr<T[]> & array, size_t size) {
    istringstream iss{ mString };
    for (auto i = 0; i < size; i++) {
        iss >> array[i];
    }
}

#endif