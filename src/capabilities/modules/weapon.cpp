#include "weapon.h"

#include "context.h"
#include "additional/stringformer.h"
#include "units/projectile.h"

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
            + StringFormer::line(static_cast<unsigned int>((timer.ready() * 4)), static_cast<unsigned int>(4))
            + "|   "
            + ((timer.ready() > 1) ? "ready" : "");
}

void Weapon::tick(Context *context, Event *event) {
    this->Module::tick(context, event);
    if(timer.count(firing)) {
        if(projectileName.size() > 0) {
            Projectile *object = static_cast<Projectile*>(context->getAssets()->createLoadable(projectileName));
            object->setMother(parent);

            object->place(parent->getPosition(), parent->getVelocity() + e172::Vector::createByAngle(getProjectileSpead(), this->parent->getAngle()), e172::Vector(), this->parent->getAngle());

            context->getUnits()->push_back(object);

            audioPlayer.play();
            //this.parent.audioPlayer.play(this, 14);
        }
    }
}

