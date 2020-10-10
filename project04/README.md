Authors:
Irene Ginani Costa Pinheiro
Thiago César Morais Diniz de Lucena

Compile:
    g++ -std=c++11 -I include/ include/tinyxml2.cpp include/lodepng.cpp src/main.cpp -o rtracer

Execute:
    ./rtracer scenes/persp.xml
    ./rtracer scenes/ortho.xml