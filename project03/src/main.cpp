#include "tinyxml2.h"
#include <iostream>
#include <memory>
#include "paramset.h"
#include "parser.h"
#include "api.h"

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

        auto w = rayTracer.film.getWidth();
        auto h = rayTracer.film.getHeight();

        for (int j = h - 1; j >= 0 ; j--) {
            for (int i = 0 ; i < w ; i++) {
                Ray r1 = rayTracer.camera.generate_ray( float(i)/float(w), float(j)/float(h), r1);
                // Generate ray with the Shirley method.
                Ray r2 = camera.generate_ray( i, j );
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