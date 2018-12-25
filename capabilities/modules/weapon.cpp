#include "weapon.h"
#include "../../context.h"

const double Weapon::DEFAULT_PROJECTILE_SPEED = 1.0;
double Weapon::getProjectileSpead() {
    Json::Value projectileSpeed = root["projectile-speed"];
    if(projectileSpeed.isNumeric()) {
        return projectileSpeed.asDouble();
    }
    return DEFAULT_PROJECTILE_SPEED;
}

Weapon::Weapon() {
}

Weapon::Weapon(Loadable *tmp) : Module (tmp) {

}

void Weapon::startFiring() {
    firing = true;
}

void Weapon::stopFiring() {
    firing = false;
}

void Weapon::loop(Context *context, Event *event) {
    if(timer.count(firing)) {
        Json::Value projectile = root["projectile"];
        if(projectile.isString()) {
            Projectile *object = static_cast<Projectile*>(context->getAssets()->copyAsset(projectile.asString()));
            object->place(parent->getPosition(), Vector::createByAngle(getProjectileSpead(), this->parent->getAngle()));
            context->getUnits()->push_back(object);

            //this.parent.audioPlayer.play(this, 14);
        }
    }
}

void Weapon::render(Renderer *renderer, Vector offset) {

}
