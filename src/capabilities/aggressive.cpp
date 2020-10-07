#include "aggressive.h"


#include <src/engine/context.h>
#include <src/units/projectile.h>
#include <src/units/camera.h>
#include <src/additional/lightparticle.h>
#include <src/capabilities/modules/weapon.h>
#include <src/capabilities/modulehandler.h>
#include <src/engine/math/math.h>
#include <src/units/ship.h>

#include <iostream>

e172::ptr<Unit> Aggressive::chooseTarget(e172::Context *context) {
    if(const auto target = context->autoIteratingEntity()) {
        if(target != parentUnit()) {
            const auto unit = e172::smart_cast<Unit>(target);
            if(unit && !unit->instanceOf<Camera>() && !unit->instanceOf<Projectile>()) {
                if(chooseTargetTimer.check()) {
                    return unit;
                }
            }
        }
    }
    return nullptr;
}

Aggressive::Aggressive() {}

void Aggressive::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(m_target && parentUnit()) {
        e172::Vector dst = m_target->position() - parentUnit()->position();
        const double dstAngle = dst.angle();
        const double dstModule = dst.module();

        //std::cout << e172::Math::radiansDirection(dstAngle, parentUnit()->rotation()) << " : " << dstAngle << " : " << parentUnit()->rotation() << "\n";
        parentUnit()->addTargetRotationForse(dstAngle, 1, 1);

        targeted = (e172::Math::radiansDistance(dstAngle, parentUnit()->rotation()) < e172::Math::Pi / 32) && !inWarp && dstModule < 400;
        const auto ship = e172::smart_cast<Ship>(parentUnit());

        if(const auto modules = parentUnit()->moduleHandler()) {
            const auto weapons = modules->modulesOfClass("Weapon");
            for(const auto module : weapons) {
                if(const auto weapon = e172::smart_cast<Weapon>(module)) {
                    weapon->setFiring(targeted);
                }
            }
            if(ship) {
                if(dstModule > 5000.0 && targeted) {
                    if(!ship->warp()) {
                        if(!ship->prepareWarp()) {
                            warpFatigueTimer.reset();
                        }
                    } else {
                        inWarp = true;
                    }
                } else if((dstModule < 1000 || warpFatigueTimer.check() || !targeted)) {
                    if(ship->abortWarp(context)) {
                        inWarp = false;
                    }
                }
            }
        }


        if(!inWarp && ship && dstModule > 200) {
            ship->thrustForward();
        }
    } else {
        targeted = false;
        m_target = chooseTarget(context);
    }
    this->Controller::proceed(context, eventHandler);
}

void Aggressive::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}

void Aggressive::onHit(e172::Context *context, int health) {
    UNUSED(context);
    UNUSED(health);
}
