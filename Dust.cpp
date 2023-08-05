#include "Dust.hpp"
#include <cmath>

Dust::Dust(Point& center)
    : center_(center)
{
}

void Dust::draw(Painter& painter) const {
    painter.draw({2000, 2800}, 8, {100, 100, 100});
}