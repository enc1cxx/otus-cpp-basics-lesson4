#include "Physics.h"
#include "World.h"
#include "Dust.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick_{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    topLeft_ = topLeft;
    bottomRight_ = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& dusts, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        move(dusts);
        collideWithBox(balls);
        collideBalls(balls, dusts);
    }
}

void Physics::spawnDust(const Ball& a, const Ball& b, std::vector<Dust>& dusts) const {
    // грубая оценка точки столкновения
    const Point collisionPointEst = (a.getCenter() + b.getCenter()) / 2;

    const Point av = a.getVelocity().vector();
    const Point bv = b.getVelocity().vector();

    for (const Point& vec: {av + bv, av - bv, bv - av, bv, av}) {
        dusts.emplace_back(collisionPointEst, vec);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if(a->getCollidable() && b->getCollidable()) {
                const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
                const double collisionDistance = a->getRadius() + b->getRadius();
                const double collisionDistance2 =
                    collisionDistance * collisionDistance;

                if (distanceBetweenCenters2 < collisionDistance2) {
                    processCollision(*a, *b, distanceBetweenCenters2);

                    spawnDust(*a, *b, dusts);
                }
            }
        }       
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        if(ball.getCollidable() == true) {
            const Point p = ball.getCenter();
            const double r = ball.getRadius();
            // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
            auto isOutOfRange = [](double v, double lo, double hi) {
                return v < lo || v > hi;
            };

            if (isOutOfRange(p.x, topLeft_.x + r, bottomRight_.x - r)) {
                Point vector = ball.getVelocity().vector();
                vector.x = -vector.x;
                ball.setVelocity(vector);
            } else if (isOutOfRange(p.y, topLeft_.y + r, bottomRight_.y - r)) {
                Point vector = ball.getVelocity().vector();
                vector.y = -vector.y;
                ball.setVelocity(vector);
            }
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick_;
        ball.setCenter(newPos);
    }
}

void Physics::move(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) {
        Point newPos =
            dust.getCenter() + dust.getVelocity().vector() * timePerTick_;
        dust.setCenter(newPos);
        dust.minusLifeTime();
        dust.minusRadius();

        for (auto it = dusts.begin(); it != dusts.end();){
            if ((*it).getLifeTime() <= 0){
                it = dusts.erase(it);   
            }
            else{
                ++it;
            }
                
        } 

    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}
