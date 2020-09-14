#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "unit.h"



class Projectile : public Unit {
    static const double DEFAULT_HIT_RADIUS;
    static const int DEFAULT_DAMAGE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;

    e172::ElapsedTimer *destroyTimer = nullptr;

    bool collision(e172::Context *context, Unit *collider);
    double damage;
    int lifetimeDelta;
    int averageLifetime;
public:
    Projectile();

    Unit *mother = nullptr;

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    void setMother(Unit *value);
};

#endif // PROJECTILE_H
