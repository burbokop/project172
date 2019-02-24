#include "weapon.h"

#include "context.h"
#include "additional/stringformer.h"
#include "units/projectile.h"

const double Weapon::DEFAULT_PROJECTILE_SPEED = 4.0;
double Weapon::getProjectileSpead() {
    Json::Value projectileSpeed = root["projectile-speed"];
    if(projectileSpeed.isNumeric()) {
        return projectileSpeed.asDouble();
    }
    return DEFAULT_PROJECTILE_SPEED;
}

Weapon::Weapon() {
    timer.reset();
}

Weapon::Weapon(Loadable *tmp) : Module (tmp) {
    timer.reset();
}

void Weapon::setFiring(bool condition) {
    firing = condition;
}

std::string Weapon::getInfo() {
    return "WP   |"
            + StringFormer::line(static_cast<unsigned int>((timer.ready() * 4)), static_cast<unsigned int>(4))
            + "|   "
            + ((timer.ready() > 1) ? "ready" : "");
}

void Weapon::loop(Context *context, Event *event) {
    this->Module::loop(context, event);
    if(timer.count(firing)) {
        Json::Value projectile = root["projectile"];
        if(projectile.isString()) {
            Projectile *object = static_cast<Projectile*>(context->getAssets()->copyAsset(projectile.asString()));
            object->setMother(parent);
            object->place(parent->getPosition(), Vector::createByAngle(getProjectileSpead(), this->parent->getAngle()), Vector(), this->parent->getAngle());
            context->getUnits()->push_back(object);

            audioPlayer.play();
            //this.parent.audioPlayer.play(this, 14);
        }
    }
}
