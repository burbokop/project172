#include "projectile.h"
#include "context.h"


const double Projectile::DEFAULT_HIT_RADIUS = 16.0;


bool Projectile::collision(Context* context, Unit *collider) {
    Camera *camera = dynamic_cast<Camera*>(collider);
    Particle *particle = dynamic_cast<Particle*>(collider);

    if(camera) std::cout << "do not shoot the camera\n";
    if(particle) std::cout << "do not shoot the particle\n";


    if(collider != mother && !camera && !particle) {

        collider->hit(context, root.get("damage", 4).asInt());
        this->hit(context, 4);
        return true;
    }
    return false;
}

Projectile::Projectile() {
    setIdleEnabled(false);
}

Projectile::Projectile(Loadable *tmp) : Movable (tmp) {
    setIdleEnabled(false);
}

void Projectile::setMother(Unit *value)
{
    mother = value;
}



void Projectile::loop(Context *context, Event *event) {
    for(Worker *worker : *(context->getUnits())) {
        Unit *unit = dynamic_cast<Unit*>(worker);
        if(unit != nullptr && unit != this) {
            if((unit->getPosition() - getPosition()).module() < DEFAULT_HIT_RADIUS) {
                collision(context, unit);
            }
        }
    }
    this->Movable::loop(context, event);
}
