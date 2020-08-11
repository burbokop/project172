#include "weapon.h"

#include "additional/stringformer.h"
#include "units/projectile.h"

#include <engine/context.h>
#include <engine/assettools/assetprovider.h>

const double Weapon::DEFAULT_PROJECTILE_SPEED = 200.0;
double Weapon::getProjectileSpead() const {
    return projectileVelocity;
}

Weapon::Weapon() {
    timer.reset();
    registerInitFunction([this](){
        projectileName = asset<std::string>("projectile");
        projectileVelocity = asset<double>("projectile-speed", DEFAULT_PROJECTILE_SPEED);
    });
}


void Weapon::setFiring(bool condition) {
    firing = condition;
}

std::string Weapon::getInfo() {
    return "WP   |"
            + StringFormer::line(static_cast<unsigned int>((timer.progress() * 4)), static_cast<unsigned int>(4))
            + "|   "
            + ((timer.progress() > 1) ? "ready" : "");
}

void Weapon::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    this->Module::proceed(context, eventHandler);
    if(timer.check(firing)) {
        if(projectileName.size() > 0) {
            Projectile *object = static_cast<Projectile*>(context->assetProvider()->createLoadable(projectileName));
            object->setMother(parent());

            object->place(parent()->getPosition(), parent()->getVelocity() + e172::Vector::createByAngle(getProjectileSpead(), parent()->getAngle()), e172::Vector(), parent()->getAngle());

            context->entities()->push_back(object);

            audioPlayer.play();
            //this.parent.audioPlayer.play(this, 14);
        }
    }
}

