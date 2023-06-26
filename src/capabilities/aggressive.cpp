#include "aggressive.h"

#include <src/context.h>
#include <src/units/projectile.h>
#include <src/units/camera.h>
#include <src/additional/lightparticle.h>
#include <src/capabilities/modules/weapon.h>
#include <src/capabilities/modulehandler.h>
#include <src/math/math.h>
#include <src/units/ship.h>

namespace proj172::core {

e172::ptr<Unit> Aggressive::chooseTarget(e172::Context *context) {
    if(const auto target = context->autoIteratingEntity()) {
        if(target != parentUnit()) {
            const auto unit = e172::smart_cast<Unit>(target);
            if(unit && !unit->instanceOf<Camera>() && !unit->instanceOf<Projectile>()) {
                if (m_chooseTargetTimer.check()) {
                    return unit;
                }
            }
        }
    }
    return nullptr;
}

void Aggressive::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    if(m_target && parentUnit()) {
        e172::Vector dst = m_target->position() - parentUnit()->position();
        const double dstAngle = dst.angle();
        const double dstModule = dst.module();

        //std::cout << e172::Math::radiansDirection(dstAngle, parentUnit()->rotation()) << " : " << dstAngle << " : " << parentUnit()->rotation() << "\n";
        parentUnit()->addTargetRotationForse(dstAngle, 1, 1);

        m_targeted = (e172::Math::radiansDistance(dstAngle, parentUnit()->rotation())
                      < e172::Math::Pi / 32)
                     && !m_inWarp && dstModule < 400;
        const auto ship = e172::smart_cast<Ship>(parentUnit());

        if(const auto modules = parentUnit()->capability<ModuleHandler>()) {
            for (const auto &weapon : modules->modules<Weapon>()) {
                weapon->setFiring(m_targeted);
            }
            if(ship) {
                if (dstModule > 5000.0 && m_targeted) {
                    if(!ship->warp()) {
                        if(!ship->prepareWarp()) {
                            m_warpFatigueTimer.reset();
                        }
                    } else {
                        m_inWarp = true;
                    }
                } else if ((dstModule < 1000 || m_warpFatigueTimer.check() || !m_targeted)) {
                    if(ship->abortWarp(context)) {
                        m_inWarp = false;
                    }
                }
            }
        }

        if (!m_inWarp && ship && dstModule > 200) {
            ship->thrustForward();
        }
    } else {
        m_targeted = false;
        m_target = chooseTarget(context);
    }
    this->Controller::proceed(context, eventHandler);
}

void Aggressive::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    UNUSED(renderer);
}

void Aggressive::onHit(e172::Context *context, int health) {
    UNUSED(context);
    UNUSED(health);
}

} // namespace proj172::core
