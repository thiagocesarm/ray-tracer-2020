#include "../ext/tinyxml2.h"
#include <iostream>
#include <memory>
#include "../parser/paramset.h"
#include "../parser/parser.h"
#include "../core/api.h"
#include "../core/camera.h"

using namespace tinyxml2;
using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
        auto t1 = std::chrono::high_resolution_clock::now();
        string sceneFile = argv[1];
        Parser parser = Parser(sceneFile);

        if (!parser.parseSceneFile()) {
            return EXIT_FAILURE;
        }

        RT3 rayTracer = RT3();
        parser.loadScene(rayTracer);
        rayTracer.run();

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        cout << ">>> TOTAL execution time: " << duration << " ms \n";
    } else {
        cout << ">>> You must provide a scene description file!" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}