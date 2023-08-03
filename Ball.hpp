#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include <cmath>

#define M_PI

class Ball {
public:
    Ball(const Point&, const Color&, const double, const Velocity&, bool);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getCollidable() const;

private:
    Velocity velocity_;
    Point center_;
    double radius_;
    double mass_ = M_PI * 1 * pow(radius_, 3) * 4. / 3;
    Color color_;
    bool is_collidable_;
};
