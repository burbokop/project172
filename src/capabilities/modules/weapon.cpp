#include "weapon.h"

#include <src/additional/stringformer.h>
#include <src/units/projectile.h>

#include <src/engine/context.h>
#include <src/engine/assettools/assetprovider.h>
#include <src/engine/gameapplication.h>


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

std::string Weapon::info() const {
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
            object->setMother(parentUnit());
            object->resetPhysicsProperties(parentUnit()->position(), parentUnit()->rotation(), parentUnit()->velocity() + e172::Vector::createByAngle(getProjectileSpead(), parentUnit()->rotation()));
            context->addEntity(object);

            audioPlayer.play();
            //this.parent.audioPlayer.play(this, 14);
        }
    }
}

