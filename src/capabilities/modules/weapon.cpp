#include "weapon.h"

#include "../../additional/stringformer.h"
#include "../../units/projectile.h"
#include <e172/assettools/assetprovider.h>
#include <e172/context.h>
#include <e172/gameapplication.h>

namespace proj172::core {

const double Weapon::s_defaultProjectileSpeed = 200.0;

double Weapon::getProjectileSpead() const {
    return projectileVelocity;
}

void Weapon::setOffset(const e172::Vector<double> &offset) {
    m_offset = offset;
}

Weapon::Weapon(e172::FactoryMeta &&meta)
    : Module(std::move(meta))
{
    m_timer.reset();
    registerInitFunction([this](){
        projectileName = asset<std::string>("projectile");
        projectileVelocity = asset<double>("projectile-speed", s_defaultProjectileSpeed);
    });
}

void Weapon::setFiring(bool condition)
{
    m_firing = condition;
}

std::string Weapon::info() const {
    return "WP   |"
           + StringFormer::line(static_cast<unsigned int>((m_timer.progress() * 4)),
                                static_cast<unsigned int>(4))
           + "|   " + ((m_timer.progress() > 1) ? "ready" : "");
}

void Weapon::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    this->Module::proceed(context, eventHandler);
    if (m_timer.check(m_firing)) {
        if(projectileName.size() > 0) {
            auto object
                = context->assetProvider()->createLoadable<Projectile>(projectileName).unwrap();
            const auto p = parentUnit();
            object->setMother(p);
            object->resetPhysicsProperties(
                p->position() + p->rotationMatrix() * m_offset,
                p->rotation(),
                p->velocity()
                    + e172::Vector<double>::createByAngle(getProjectileSpead(), p->rotation()));
            context->addEntity(object);
            m_audioPlayer.play();
        }
    }
}

} // namespace proj172::core
