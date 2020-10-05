#include "tinyxml2.h"
#include <iostream>
#include <memory>
#include "paramset.h"
#include "parser.h"
#include "api.h"
#include "camera.h"

using namespace tinyxml2;
using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
        string sceneFile = argv[1];
        Parser parser = Parser(sceneFile);

        if (!parser.parseSceneFile()) {
            return EXIT_FAILURE;
        }

        RT3 rayTracer = RT3();
        parser.loadScene(rayTracer);
        
        auto w = rayTracer.camera->film->getWidth();
        auto h = rayTracer.camera->film->getHeight();

        for (int j = h - 1; j >= 0 ; j--) {
            for (int i = 0 ; i < w ; i++) {
                Ray ray = rayTracer.camera->generate_ray( i, j );
                auto color = rayTracer.background.sample( float(i)/float(w), float(j)/float(h) );
                for (const auto p : rayTracer.objects) {
                    if (p->intersect_p( ray )) {
                        color = Color {255, 0, 0 }; // simply paint the object red
                    }
                }
                rayTracer.camera->film->drawPixel(i, j, color);
            }
        }

        rayTracer.camera->film->printToFile();
    } else {
        cout << ">>> You must provide a scene description file!" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}