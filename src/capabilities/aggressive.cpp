#include "aggressive.h"


#include <src/engine/objectregistry.h>
#include <src/units/particle.h>
#include <src/units/projectile.h>
#include <src/units/camera.h>
#include <src/additional/lightparticle.h>
#include <src/old_debug.h>
#include <src/capabilities/modules/weapon.h>




Unit *Aggressive::chooseTarget() {
    if(targets.size() <= 0)
        return nullptr;

    Entity *target = targets.front();

    if(target == e172::Alive) {
        Camera *camera = dynamic_cast<Camera*>(target);
        Particle *particle = dynamic_cast<Particle*>(target);
        LightParticle *lightParticle = dynamic_cast<LightParticle*>(target);
        Projectile *projectile = dynamic_cast<Projectile*>(target);

        return camera || particle || lightParticle || projectile ? nullptr : dynamic_cast<Unit*>(target);
    } else {
        old::Debug::err(old::Debug::Code::APPEAL_TO_REMOVED, __PRETTY_FUNCTION__);
        return nullptr;
    }
}

Aggressive::Aggressive(std::list<Entity *> units) {
    for(auto u : units) {
        if(u->instanceOf<Unit>()) {
            targets.push_back(u);
        }
    }
    target = chooseTarget();
}

void Aggressive::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
     if(target == e172::Alive) {
        if(target != nullptr && parentUnit() != nullptr && target->instanceOf<Ship>() && target != parentUnit()) {
            e172::Vector dst = target->position() - parentUnit()->position();
            const double dstAngle = dst.angle();
            const double dstModule = dst.module();

            parentUnit()->rotateToAngle(context, dstAngle);
            targeted = parentUnit()->isOnAngle(context, dstAngle) && !inWarp && dstModule < 400;
            Ship *ship = dynamic_cast<Ship*>(parentUnit());

            ModuleHandler *modules = parentUnit()->getModuleHandler();
            if(modules) {
                std::vector<Module*> *weapons = modules->getModulesByClass("Weapon");

                if(weapons) {
                    for(Module *module : *weapons) {
                        Weapon *weapon = dynamic_cast<Weapon*>(module);
                        if(weapon) {
                            weapon->setFiring(targeted);
                        }
                    }
                }
                if(ship) {
                    if(dstModule > 5000.0) {
                        if(!ship->warp()) {
                            if(!ship->prepareWarp()) {
                                stopWarpTrigger.enable();
                                warpFatigueTimer.reset();
                            }
                        } else {
                            inWarp = true;
                        }
                    } else if((dstModule < 1000 || warpFatigueTimer.check()) && stopWarpTrigger.check()) {
                        if(!ship->abortWarp(context)) {
                            stopWarpTrigger.disanable();
                        } else {
                            inWarp = false;
                        }
                    }
                }
            }


            if(ship && dstModule > 200) {
                ship->accelerateForward();
            }
    /*
            if(getPersonalKey(event, "armor")) {
                releaseArmor();
            }
    */
        } else {
            target = chooseTarget();
        }
    } else {
        old::Debug::err(old::Debug::Code::APPEAL_TO_REMOVED, __PRETTY_FUNCTION__);
        targeted = false;
        target = chooseTarget();
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
