#ifndef WEAPON_H
#define WEAPON_H


#include "capabilities/modules/module.h"


class Weapon : public Module {
private:
    static const double DEFAULT_PROJECTILE_SPEED;
    double getProjectileSpead() const;

    std::string projectileName;
    double projectileVelocity;
protected:
    bool firing = false;

public:
    Weapon();

    void setFiring(bool condition);
    std::string getInfo() override;

    // Worker interface
public:
    void tick(Context *context, Event *event) override;
};

#endif // WEAPON_H
