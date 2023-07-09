#include "projectile.h"

#include "../additional/lightparticle.h"
#include "camera.h"
#include <e172/context.h>

namespace proj172::core {

const double Projectile::DEFAULT_HIT_RADIUS = 16.0;
const int Projectile::DEFAULT_DAMAGE = 4;

const int Projectile::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int Projectile::DEFAULT_LIFE_TIME_DELTA = 4000;

bool Projectile::collision(e172::Context* context, const e172::ptr<Unit> &collider) {
    if (!collider->instanceOf<Camera>() && !collider->instanceOf<LightParticle>()
        && !collider->instanceOf<Projectile>() && collider != m_mother) {
        collider->hit(context, m_damage);
        this->hit(context, DEFAULT_DAMAGE);
        return true;
    }
    return false;
}

Projectile::Projectile(e172::FactoryMeta &&meta)
    : Unit(std::move(meta))
{
    registerInitFunction([this]() {
        m_damage = asset<double>("damage", DEFAULT_DAMAGE);
        m_lifetimeDelta = asset<double>("lifetime-delta", DEFAULT_LIFE_TIME_DELTA);
        m_averageLifetime = asset<double>("lifetime", DEFAULT_AVERAGE_LIFE_TIME);
        m_destroyTimer = new e172::ElapsedTimer(
            (rand() % (2 * m_lifetimeDelta) + (m_averageLifetime - m_lifetimeDelta)));
        m_destroyTimer->reset();
        setFriction(0);
    });
}

void Projectile::setMother(const e172::ptr<Unit> &value) {
    m_mother = value;
}

void Projectile::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    if (m_destroyTimer && m_destroyTimer->check()) {
        context->emitMessage(e172::Context::DestroyEntity, entityId());
    }

    const auto entities = context->entities();
    for (const auto &e : entities) {
        if(const auto unit = e172::smart_cast<Unit>(e)) {
            if(unit != this) {
                if((unit->position() - position()).module() < DEFAULT_HIT_RADIUS) {
                    collision(context, unit);
                }
            }
        }
    }
    Unit::proceed(context, eventHandler);
}

} // namespace proj172::core
