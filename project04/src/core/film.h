#ifndef _FILM_
#define _FILM_

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "color.h"
#include "../ext/lodepng.h"

using namespace std;

class Film {
    private:
        string type;
        int width;
        int height;
        string filename;
        string imgType;
        unique_ptr<Color[]> pixels;
        int crop_window[4];
    public:
        Film(){};
        Film(string mType, int mXRes, int mYRes, string mFilename, string mImgType, int * mCrop_window);
        int getWidth();
        int getHeight();
        bool isValidCoordinate(int, int);
        void drawPixel(int, int, Color);
        void printToFile();
        void printToPngFile();
};

Film::Film(string mType, int xRes, int yRes, string mFilename, string mImgType, int * mCrop_window) {
    type = mType;
    width = xRes;
    height = yRes;
    filename = mFilename;
    imgType = mImgType;

    if (mCrop_window != nullptr) {
        crop_window[0] = mCrop_window[0];
        crop_window[1] = mCrop_window[1];
        crop_window[2] = mCrop_window[2];
        crop_window[3] = mCrop_window[3];
    }
    
    pixels = std::unique_ptr<Color[]>(new Color[width*height]);
    std::fill(pixels.get(), pixels.get() + (width * height), Color(255,255,255));
}

int Film::getWidth() {
    return width;
}

int Film::getHeight() {
    return height;
}

bool Film::isValidCoordinate(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Film::drawPixel(int i, int j, Color color) {
    if (!isValidCoordinate(i, j)) {
        return;
    }
    int p_index = j * width + i;
    pixels[p_index] = color;
}

void Film::printToFile() {
    if (imgType == "ppm") {
        std::ofstream outfile;
        outfile.open(filename);
        outfile << "P3" << std::endl;
        outfile << width << " " << height << std::endl;
        outfile << "255" << std::endl;
        auto line_end = width*3;
        for (auto i = 0; i < (height*width); ++i) {
            outfile << int(pixels[i].r()) << " ";
            outfile << int(pixels[i].g()) << " ";
            outfile << int(pixels[i].b()) << " ";
            if (i % line_end == line_end - 1) { outfile << std::endl; }  
        }
        outfile.close();
    } else if (imgType == "png") {
        vector<unsigned char> pngVector;
        for(auto i = 0; i < width * height; i++) {
            pngVector.push_back(pixels[i].r());
            pngVector.push_back(pixels[i].g());
            pngVector.push_back(pixels[i].b());
            pngVector.push_back(255);
        }

        unsigned error = lodepng::encode(filename, pngVector, width, height);
        if (error) {
            cout << ">>> Could not encode PNG image. Error " << error << ": " << lodepng_error_text(error) << endl;
        }
    }
}

#endif