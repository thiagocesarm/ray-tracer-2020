Compile:
    clang++ -std=c++11 -I include/ include/tinyxml2.cpp src/main.cpp -o rtracer

Execute:
    ./rtracer scenes/simple_bkg.xml
    ./rtracer scenes/interpolated_bkg.xml