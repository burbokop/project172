#pragma once

#include "unit.h"
#include <src/utility/ptr.h>

namespace proj172::core {

class Projectile : public Unit {
public:
    Projectile(e172::FactoryMeta &&meta);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    void setMother(const e172::ptr<Unit> &value);

private:
    bool collision(e172::Context *context, const e172::ptr<Unit> &collider);

private:
    static const double DEFAULT_HIT_RADIUS;
    static const int DEFAULT_DAMAGE;
    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;

    e172::ptr<Unit> m_mother;
    e172::ElapsedTimer *m_destroyTimer = nullptr;
    double m_damage;
    int m_lifetimeDelta;
    int m_averageLifetime;
};

} // namespace proj172::core
