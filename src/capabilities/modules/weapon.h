#pragma once

#include "module.h"

namespace proj172::core {

class Weapon : public Module
{
public:
    Weapon(e172::FactoryMeta &&meta);

    void setFiring(bool condition);
    std::string info() const override;

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    e172::Vector<double> offset() const { return m_offset; }
    void setOffset(const e172::Vector<double> &offset);

protected:
    bool m_firing = false;

private:
    double getProjectileSpead() const;

private:
    static const double s_defaultProjectileSpeed;

    std::string projectileName;
    double projectileVelocity;
    e172::Vector<double> m_offset;
};

} // namespace proj172::core
