Authors:
- Irene Ginani Costa Pinheiro
- Thiago César Morais Diniz de Lucena

Compile:
    g++ -std=c++11 -I src/ext src/ext/tinyxml2.cpp src/ext/lodepng.cpp src/main/main.cpp -o rtracer

Execute:
    ./rtracer scenes/flat_material.xml
    ./rtracer scenes/flat_material_ortho.xml