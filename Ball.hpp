#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
public:
    Ball(const Point&, const Color&, const double, const Point&, bool);
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
    Color color_;
    bool is_collidable_;
    double mass_;
};
