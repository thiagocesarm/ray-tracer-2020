#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <sstream>
#include "tinyxml2.h"
#include "paramset.h"
#include "scene_xml_params.h"
#include "api.h"
#include "rt3.h"

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

        API::setCamera(*currentParamSet);
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