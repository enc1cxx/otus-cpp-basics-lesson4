#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Dust {
public:
    Dust() = default;
    ~Dust() = default;

    Dust(Point& center);

    void draw(Painter& painter) const;

  private:
    double radius_ = 20;
    Color color_{100, 100, 100};
    Point center_;
};
