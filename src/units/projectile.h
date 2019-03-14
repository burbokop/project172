#ifndef PROJECTILE_H
#define PROJECTILE_H


#include "units/movable.h"


class Projectile : public Movable {
private:
    static const double DEFAULT_HIT_RADIUS;
    static const int DEFAULT_DAMAGE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;

    Timer *destroyTimer = nullptr;

    bool collision(Context *context, Unit *collider);

public:
    Projectile();
    Projectile(Loadable *tmp);

    Unit *mother = nullptr;

    // Worker interface
public:
    void tick(Context *context, Event *event);
    void setMother(Unit *value);
};

#endif // PROJECTILE_H
