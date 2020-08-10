#ifndef PROJECTILE_H
#define PROJECTILE_H


#include "units/movable.h"


class Projectile : public Movable {
    static const double DEFAULT_HIT_RADIUS;
    static const int DEFAULT_DAMAGE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;

    Timer *destroyTimer = nullptr;

    bool collision(Context *context, Unit *collider);
    double damage;
    int lifetimeDelta;
    int averageLifetime;
public:
    Projectile();

    Unit *mother = nullptr;

    // Worker interface
public:
    void tick(Context *context, e172::AbstractEventHandler *eventHandler) override;
    void setMother(Unit *value);
};

#endif // PROJECTILE_H
