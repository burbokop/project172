#include "aggressive.h"


#include <src/engine/context.h>
#include <src/engine/objectregistry.h>
#include <src/units/projectile.h>
#include <src/units/camera.h>
#include <src/additional/lightparticle.h>
#include <src/capabilities/modules/weapon.h>
#include <src/capabilities/modulehandler.h>
#include <src/engine/math/math.h>
#include <src/units/ship.h>

#include <iostream>

Unit *Aggressive::chooseTarget(e172::Context *context) {
    if(chooseTargetTimer.check()) {
        Entity *target = context->autoIteratingEntity();
        if(target == e172::Alive) {
            const auto unit = target->cast<Unit>();
            if(unit && !unit->instanceOf<Camera>() && !unit->instanceOf<Projectile>()) {
                //std::cout << __PRETTY_FUNCTION__ << " " << unit << "\n";
                return unit;
            }
        }
    }
    return nullptr;
}

Aggressive::Aggressive() {}

void Aggressive::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
     if(target == e172::Alive) {
        if(target && parentUnit() && target->instanceOf<Ship>() && target != parentUnit()) {
            e172::Vector dst = target->position() - parentUnit()->position();
            const double dstAngle = dst.angle();
            const double dstModule = dst.module();

            //std::cout << e172::Math::radiansDirection(dstAngle, parentUnit()->rotation()) << " : " << dstAngle << " : " << parentUnit()->rotation() << "\n";
            parentUnit()->addTargetRotationForse(dstAngle, 1, 1);

            targeted = (e172::Math::radiansDistance(dstAngle, parentUnit()->rotation()) < e172::Math::Pi / 32) && !inWarp && dstModule < 400;
            Ship *ship = dynamic_cast<Ship*>(parentUnit());

            ModuleHandler *modules = parentUnit()->moduleHandler();
            if(modules) {
                auto weapons = modules->modulesOfClass("Weapon");

                for(Module *module : weapons) {
                    Weapon *weapon = dynamic_cast<Weapon*>(module);
                    if(weapon) {
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
    /*
            if(getPersonalKey(event, "armor")) {
                releaseArmor();
            }
    */
        } else {
            target = chooseTarget(context);
        }
    } else {
        targeted = false;
        target = chooseTarget(context);
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
