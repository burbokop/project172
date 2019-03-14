#ifndef WEAPON_H
#define WEAPON_H


#include "capabilities/modules/module.h"


class Weapon : public Module {
private:
    static const double DEFAULT_PROJECTILE_SPEED;
    double getProjectileSpead();

protected:
    bool firing = false;

public:
    Weapon();
    Weapon(Loadable *tmp);

    void setFiring(bool condition);
    std::string getInfo();

    // Worker interface
public:
    void tick(Context *context, Event *event);
};

#endif // WEAPON_H
