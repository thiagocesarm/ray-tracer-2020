#ifndef _BACKGROUND_
#define _BACKGROUND_

#include "../core/color.h"

class Background {
    private:
        Color corners[2][2];
    public:
        Background(){};
        Background(Color);
        Background(Color, Color, Color, Color);
        Color sample(double, double);
};

Background::Background(Color solid_color) {
    corners[0][0] = solid_color;
    corners[0][1] = solid_color;
    corners[1][1] = solid_color;
    corners[1][0] = solid_color;
}

Background::Background(Color bottom_left, Color top_left, Color top_right, Color bottom_right) {
    corners[0][0] = bottom_left;
    corners[0][1] = top_left;
    corners[1][1] = top_right;
    corners[1][0] = bottom_right;
}

Color Background::sample(double i, double j) {
    double i_comp = 1 - i;
    double j_comp = 1 - j;

    double r_val_bottom = i_comp*corners[0][1].r() + i*corners[1][1].r();
    double g_val_bottom = i_comp*corners[0][1].g() + i*corners[1][1].g();
    double b_val_bottom = i_comp*corners[0][1].b() + i*corners[1][1].b();

    double r_val_top = i_comp*corners[0][0].r() + i*corners[1][0].r();
    double g_val_top = i_comp*corners[0][0].g() + i*corners[1][0].g();
    double b_val_top = i_comp*corners[0][0].b() + i*corners[1][0].b();

    double r_val = j_comp*r_val_bottom + j*r_val_top;
    double g_val = j_comp*g_val_bottom + j*g_val_top;
    double b_val = j_comp*b_val_bottom + j*b_val_top;

    // [0, 255] to [0, 1] values
    return Color(float(r_val / 255), float(g_val / 255), float(b_val / 255));
}

#endif