#include "projectile.h"

#include "context.h"
#include "units/particle.h"
#include "units/camera.h"
#include "additional/lightparticle.h"
#include "objectregistry.h"
#include "debug.h"

const double Projectile::DEFAULT_HIT_RADIUS = 16.0;
const int Projectile::DEFAULT_DAMAGE = 4;


const int Projectile::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int Projectile::DEFAULT_LIFE_TIME_DELTA = 4000;


bool Projectile::collision(Context* context, Unit *collider) {
    if(
        collider->isNot<Camera*>() &&
        collider->isNot<Particle*>() &&
        collider->isNot<LightParticle*>() &&
        collider->isNot<Projectile*>() &&
        collider != mother
    ) {
        collider->hit(context, root.get("damage", DEFAULT_DAMAGE).asInt());
        this->hit(context, DEFAULT_DAMAGE);
        return true;
    }
    return false;
}

Projectile::Projectile() {
    setIdleEnabled(false);
    destroyTimer = new Timer((rand() % (2 * DEFAULT_LIFE_TIME_DELTA)) + (DEFAULT_AVERAGE_LIFE_TIME - DEFAULT_LIFE_TIME_DELTA));
    destroyTimer->reset();
}

Projectile::Projectile(Loadable *tmp) : Movable (tmp) {
    setIdleEnabled(false);
    destroyTimer = new Timer((rand() % (2 * root.get("lifetime-delta", DEFAULT_LIFE_TIME_DELTA).asInt()) + (root.get("lifetime", DEFAULT_AVERAGE_LIFE_TIME).asInt() - root.get("lifetime-delta", DEFAULT_LIFE_TIME_DELTA).asInt())));
    destroyTimer->reset();
}

void Projectile::setMother(Unit *value) {
    mother = value;
}

void Projectile::loop(Context *context, Event *event) {
    if(destroyTimer && destroyTimer->count()) {
        context->addEvent(this, Context::DELETE_UNIT);
    }

    for(Worker *worker : *(context->getUnits())) {
        EXISTS(worker) {
            Unit *unit = dynamic_cast<Unit*>(worker);
            if(unit != nullptr && unit != this) {
                if((unit->getPosition() - getPosition()).module() < DEFAULT_HIT_RADIUS) {
                    collision(context, unit);
                }
            }
        } else {
            Debug::err(Debug::APPEAL_TO_REMOVED, DEBUG_IMPRINT);
        }
    }
    this->Movable::loop(context, event);
}