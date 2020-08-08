#include "aggressive.h"


#include "objectregistry.h"
#include "units/particle.h"
#include "units/projectile.h"
#include "units/camera.h"
#include "additional/lightparticle.h"
#include "debug.h"
#include "capabilities/modules/weapon.h"




Unit *Aggressive::chooseTarget() {
    if(targets == nullptr) return nullptr;
    Worker *target = targets->at(static_cast<unsigned long>(rand()) % targets->size());

    EXISTS(target) {
        Camera *camera = dynamic_cast<Camera*>(target);
        Particle *particle = dynamic_cast<Particle*>(target);
        LightParticle *lightParticle = dynamic_cast<LightParticle*>(target);
        Projectile *projectile = dynamic_cast<Projectile*>(target);

        return camera || particle || lightParticle || projectile ? nullptr : dynamic_cast<Unit*>(target);
    } else {
        Debug::err(Debug::Code::APPEAL_TO_REMOVED, __PRETTY_FUNCTION__);
        return nullptr;
    }
}

Aggressive::Aggressive(std::vector<Worker *> *units) {
    targets = units;
    target = chooseTarget();
}

void Aggressive::tick(Context *context, Event *event) {
    EXISTS(target) {
        if(target != nullptr && parent() != nullptr && target->is<Ship*>() && target != parent()) {
            e172::Vector dst = target->getPosition() - parent()->getPosition();
            const double dstAngle = dst.angle();
            const double dstModule = dst.module();

            parent()->rotateToAngle(dstAngle);
            targeted = parent()->isOnAngle(dstAngle) && !inWarp && dstModule < 400;
            Ship *ship = dynamic_cast<Ship*>(parent());

            ModuleHandler *modules = parent()->getModuleHandler();
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
                    } else if((dstModule < 1000 || warpFatigueTimer.count()) && stopWarpTrigger.check()) {
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
        Debug::err(Debug::Code::APPEAL_TO_REMOVED, __PRETTY_FUNCTION__);
        targeted = false;
        target = chooseTarget();
    }
    this->Controller::tick(context, event);
}

void Aggressive::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}

void Aggressive::onHit(Context *context, int health) {
    UNUSED(context);
    UNUSED(health);
}
