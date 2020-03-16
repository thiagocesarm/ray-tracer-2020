#include "tinyxml2.h"
#include <iostream>
#include <memory>
#include "paramset.h"
#include "parser.h"

using namespace tinyxml2;
using namespace std;

int main(int argc, char** argv) {

    if (argc > 1) {
        string sceneFile = argv[1];
        Parser parser = Parser(sceneFile);
        if (!parser.parseSceneFile()) {
            return EXIT_FAILURE;
        }
    } else {
        cout << ">>> You must provide a scene description file!" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
    return 0;
}