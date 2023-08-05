#include "Color.h"

Color::Color() = default;

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}

double Color::red() const {
    return r;
}

double Color::green() const {
    return g;
}

double Color::blue() const {
    return b;
}

void Color::set_color(double red, double green, double blue) {
    r = red;
    g = green;
    b = blue;
}
