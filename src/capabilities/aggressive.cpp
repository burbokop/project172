#include "aggressive.h"


#include "objectregistry.h"
#include "units/particle.h"
#include "units/projectile.h"
#include "units/camera.h"
#include "additional/lightparticle.h"
#include "debug.h"
#include "capabilities/modules/weapon.h"


const double Aggressive::ANGLE_DELTA = 0.005;


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
        Debug::err(Debug::APPEAL_TO_REMOVED, DEBUG_IMPRINT);
        return nullptr;
    }
}

Aggressive::Aggressive(std::vector<Worker *> *units) {
    targets = units;
    target = chooseTarget();
}

void Aggressive::loop(Context *context, Event *event) {
    EXISTS(target) {
        if(target != nullptr && parent != nullptr && target->is<Ship*>() && target != parent) {

            Vector dst = target->getPosition() - parent->getPosition();
            const double dstAngle = dst.angle();
            const double dstModule = dst.module();

            if(parent->getAngle() > dstAngle + ANGLE_DELTA) {
                parent->rotateLeft() ;
            } else if(parent->getAngle() < dstAngle - ANGLE_DELTA) {
                parent->rotateRight();
            }

            targeted = !(parent->getAngle() > dstAngle + ANGLE_DELTA * 2 || parent->getAngle() < dstAngle - ANGLE_DELTA * 2);

            Ship *ship = dynamic_cast<Ship*>(parent);

            ModuleHandler *modules = parent->getModuleHandler();
            if(modules) {
                std::vector<Module*> *weapons = modules->getModulesByClass("weapon");

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
                        }
                    } else if((dstModule < 1000 || warpFatigueTimer.count()) && stopWarpTrigger.check()) {
                        if(!ship->abortWarp(context)) {
                            stopWarpTrigger.disanable();
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
        Debug::err(Debug::APPEAL_TO_REMOVED, DEBUG_IMPRINT);
        targeted = false;
        target = chooseTarget();
    }
    this->Controller::loop(context, event);
}

void Aggressive::render(Renderer *renderer) {
    UNUSED(renderer);
}

void Aggressive::onHit(Context *context, int health) {
    UNUSED(context);
    UNUSED(health);
}