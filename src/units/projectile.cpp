#include "projectile.h"

#include "camera.h"

#include <src/additional/lightparticle.h>
#include <src/engine/objectregistry.h>
#include <src/engine/context.h>

const double Projectile::DEFAULT_HIT_RADIUS = 16.0;
const int Projectile::DEFAULT_DAMAGE = 4;

const int Projectile::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int Projectile::DEFAULT_LIFE_TIME_DELTA = 4000;


bool Projectile::collision(e172::Context* context, Unit *collider) {
    if(
        !collider->instanceOf<Camera>() &&
        !collider->instanceOf<LightParticle>() &&
        !collider->instanceOf<Projectile>() &&
        collider != mother
    ) {
        collider->hit(context, damage);
        this->hit(context, DEFAULT_DAMAGE);
        return true;
    }
    return false;
}

Projectile::Projectile() {
    registerInitFunction([this]() {
        damage = asset<double>("damage", DEFAULT_DAMAGE);
        lifetimeDelta = asset<double>("lifetime-delta", DEFAULT_LIFE_TIME_DELTA);
        averageLifetime = asset<double>("lifetime", DEFAULT_AVERAGE_LIFE_TIME);
        setFriction(0);
        destroyTimer = new e172::ElapsedTimer((rand() % (2 * lifetimeDelta) + (averageLifetime - lifetimeDelta)));
        destroyTimer->reset();
    });
}

void Projectile::setMother(Unit *value) {
    mother = value;
}

void Projectile::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(destroyTimer && destroyTimer->check()) {
        context->emitMessage(e172::Context::DESTROY_ENTITY, entityId());
    }

    const auto entities = context->entities();
    for(Entity *e : entities) {
        if(e == e172::Alive) {
            Unit *unit = dynamic_cast<Unit*>(e);
            if(unit != nullptr && unit != this) {
                if((unit->position() - position()).module() < DEFAULT_HIT_RADIUS) {
                    collision(context, unit);
                }
            }
        }
    }
    Unit::proceed(context, eventHandler);
}

