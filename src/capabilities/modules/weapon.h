#ifndef WEAPON_H
#define WEAPON_H


#include "module.h"


class Weapon : public Module {
private:
    static const double DEFAULT_PROJECTILE_SPEED;
    double getProjectileSpead() const;

    std::string projectileName;
    double projectileVelocity;
    e172::Vector m_offset;
protected:
    bool firing = false;

public:
    Weapon();

    void setFiring(bool condition);
    std::string info() const override;

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    e172::Vector offset() const;
    void setOffset(const e172::Vector &offset);
};

#endif // WEAPON_H
