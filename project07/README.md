Authors:
- Irene Ginani Costa Pinheiro
- Thiago César Morais Diniz de Lucena

Compile:
    g++ -std=c++11 -I src/ext src/ext/*.cpp src/main/main.cpp -o rtracer

Execute:
    ./rtracer scenes/teapot_persp.xml
    ./rtracer scenes/teapot_ortho.xml
    ./rtracer scenes/table.xml