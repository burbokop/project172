#include "movable.h"
#include <src/capabilities/modules/engine.h>
#include <math.h>
#include <src/engine/math/math.h>
#include <src/engine/context.h>
#include <src/capabilities/modulehandler.h>


void Movable::setIdleEnabled(bool value) {
    idleEnabled = value;
}

void Movable::forcedMaxSpeed(double value) {
    forcedMaxSpeedEnabled = true;
    forcedMaxSpeedValue = value;
}

void Movable::disableForcedMaxSpeed() {
    forcedMaxSpeedEnabled = false;
}

bool Movable::onAcceleration(bool start) {
    ModuleHandler *modules = moduleHandler();
    if(modules) {
        std::vector<Module*> *engines = modules->getModulesByClass("Engine");
        if(engines) {
            for(Module *module : *engines) {
                Engine *engine = dynamic_cast<Engine*>(module);
                if(engine) {
                    if(start) {
                        if(engine->forward()) return true;
                    } else {
                        engine->stop();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void Movable::setRelativisticVelocity(bool value) {
    relativisticVelocity = value;
}



Movable::Movable() {}


bool Movable::accelerateForward() {
    if(!accelerationLocked) {
        ModuleHandler *modules = moduleHandler();
        if(modules && modules->hasModuleOfClass("Engine")) {
            addForce(e172::Vector::createByAngle(movingForce(), rotation()));
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}

bool Movable::accelerateLeft() {
    if(!accelerationLocked) {
        ModuleHandler *modules = moduleHandler();
        if(modules && modules->hasModuleOfClass("Thruster")) {
            addForce(e172::Vector::createByAngle(movingForce(), rotation() - M_PI / 2));
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}

bool Movable::accelerateRight() {
    if(!accelerationLocked) {
        ModuleHandler *modules = moduleHandler();
        if(modules && modules->hasModuleOfClass("Thruster")) {
            addForce(e172::Vector::createByAngle(movingForce(), rotation() + M_PI / 2));
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}


void Movable::accelerateIdle() {
    if(!accelerationLocked && idleEnabled) {
        addForce(velocity().module() > StopMovingVelocity ?
                     e172::Vector::createByAngle(DefaultIdleSpead, velocity().angle()) :
                     e172::Vector());
    }
}

void Movable::accelerate(e172::Vector acceleration) {
    if(!accelerationLocked) {
        addForce(acceleration);
        accelerationLocked = true;
    }
}


void Movable::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    accelerateIdle();
    setMaxRotationVelocity(std::pow(2, -velocity().module() * 0.004) * DefaultMaxRotationSpeed);
    accelerationLocked = false;
    Unit::proceed(context, eventHandler);
}

