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

void Color::set_red(double red) {
    this->r = red;
}

void Color::set_green(double green) {
    this->g = green;
}

void Color::set_blue(double blue) {
    this->b = blue;
}
