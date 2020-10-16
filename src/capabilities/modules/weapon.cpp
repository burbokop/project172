#include "weapon.h"

#include <src/additional/stringformer.h>
#include <src/units/projectile.h>

#include <src/context.h>
#include <src/assettools/assetprovider.h>
#include <src/gameapplication.h>


const double Weapon::DEFAULT_PROJECTILE_SPEED = 200.0;
double Weapon::getProjectileSpead() const {
    return projectileVelocity;
}

e172::Vector Weapon::offset() const {
    return m_offset;
}

void Weapon::setOffset(const e172::Vector &offset) {
    m_offset = offset;
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
            auto object = context->assetProvider()->createLoadable<Projectile>(projectileName);
            const auto p = parentUnit();
            object->setMother(p);
            object->resetPhysicsProperties(p->position() + p->rotationMatrix() * m_offset, p->rotation(), p->velocity() + e172::Vector::createByAngle(getProjectileSpead(), p->rotation()));
            context->addEntity(object);
            audioPlayer.play();
        }
    }
}

