#pragma once

#include <vector>

#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Dust {
public:
    Dust() = default;
    ~Dust() = default;

    Dust(const Point& center, const Velocity& velocity);

    void draw(Painter& painter) const;

    Velocity getVelocity() const;
    Point getCenter() const;
    void setCenter(const Point& center);
    void minusLifeTime();
    void minusRadius(); //пыль уменьшается в размерах во временем
    int getLifeTime() const;
    

  private:
    double radius_ = 30;
    Color color_{0, 0, 0};
    Point center_;
    Velocity velocity_;
    int life_time_ = 300;
};
