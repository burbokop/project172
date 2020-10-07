#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "unit.h"

#include <src/engine/utility/ptr.h>



class Projectile : public Unit {
    static const double DEFAULT_HIT_RADIUS;
    static const int DEFAULT_DAMAGE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;

    e172::ElapsedTimer *destroyTimer = nullptr;

    bool collision(e172::Context *context, const e172::ptr<Unit> &collider);
    double damage;
    int lifetimeDelta;
    int averageLifetime;
public:
    Projectile();

    e172::ptr<Unit> mother;

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    void setMother(const e172::ptr<Unit> &value);
};

#endif // PROJECTILE_H
