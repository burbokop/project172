#ifndef WEAPON_H
#define WEAPON_H

#include "capabilities/modules/module.h"
#include "units/projectile.h"


class Weapon : public Module
{
private:
    static const double DEFAULT_PROJECTILE_SPEED;
    double getProjectileSpead();

protected:
    bool firing = false;

public:
    Weapon();
    Weapon(Loadable *tmp);

    void setFiring(bool condition);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // WEAPON_H
