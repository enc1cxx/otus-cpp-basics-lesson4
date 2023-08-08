#include "Dust.hpp"
#include <cmath>


Dust::Dust(const Point& center, const Velocity& velocity)
    : center_(center), velocity_(velocity)
{
    
}

void Dust::draw(Painter& painter) const {
    painter.draw(center_, radius_, color_);
}

Velocity Dust::getVelocity() const {
    return velocity_;
}

Point Dust::getCenter() const {
    return center_;
}

void Dust::setCenter(const Point& center) {
    center_ = center;
}

void Dust::minusLifeTime() {
    --life_time_;
}

void Dust::minusRadius() {
    radius_ -= 0.1;
}

int Dust::getLifeTime() const {
    return life_time_;
}


