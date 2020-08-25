#ifndef WEAPON_H
#define WEAPON_H


#include "module.h"


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

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
};

#endif // WEAPON_H
