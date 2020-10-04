#include "tinyxml2.h"
#include <iostream>
#include <memory>
#include "paramset.h"
#include "parser.h"
#include "api.h"
#include "orthographic.h"

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
        OrthographicCamera oc = OrthographicCamera();
        if (rayTracer.camera.type == "orthografic") {
            oc.set_parallel_box(rayTracer.camera.screen_window[0], rayTracer.camera.screen_window[1], rayTracer.camera.screen_window[2], rayTracer.camera.screen_window[3]);
        }
        
        auto w = rayTracer.film.getWidth();
        auto h = rayTracer.film.getHeight();

        for (int j = h - 1; j >= 0 ; j--) {
            for (int i = 0 ; i < w ; i++) {
                // Generate ray with the Shirley method.
                if (rayTracer.camera.type == "orthografic") {
                    Ray r2 = oc.generate_ray( i, j , w, h);
                }
                // Print out the two rays, that must be the same (regardless of the method).
                auto color = rayTracer.background.sample( float(i)/float(w), float(j)/float(h) );
                rayTracer.film.drawPixel(i, j, color);
            }
        }

        rayTracer.film.printToFile();
    } else {
        cout << ">>> You must provide a scene description file!" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}