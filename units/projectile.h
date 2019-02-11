#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "units/camera.h"


class Projectile : public Movable {
private:
    static const double DEFAULT_HIT_RADIUS;

    bool collision(Context *context, Unit *collider);

public:
    Projectile();
    Projectile(Loadable *tmp);

    Unit *mother = nullptr;

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void setMother(Unit *value);
};

#endif // PROJECTILE_H
