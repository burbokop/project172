#include "movable.h"
#include "capabilities/modules/engine.h"
#include "context.h"
#include "time/time.h"
#include "additional/math.h"
#include <math.h>

const double Movable::STOP_MOVING_VELOCITY = 1;
const double Movable::DEFAULT_ACCELERATION_VALUE = 120;
const double Movable::DEFAULT_RELEASE_SPEAD = 1;
const double Movable::DEFAULT_MAX_SPEED = 120;
const double Movable::DEFAULT_IDLE_SPEAD = -60;
const double Movable::RELATIVISTIC_PURSUIT_COEFFICIENT = 0.0025;



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
    ModuleHandler *modules = getModuleHandler();
    if(modules) {
        std::vector<Module*> *engines = modules->getModulesByClass("engine");
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

double Movable::getAccelerationValue() {
    Json::Value value = root["acceleration"];
    if(value.isNumeric()) {
        return value.asDouble();
    }
    return DEFAULT_ACCELERATION_VALUE;
}

double Movable::getMaxSpeed() {
    if(!forcedMaxSpeedEnabled) {
        Json::Value value = root["max-speed"];
        if(value.isNumeric()) {
            return value.asDouble();
        }
        return DEFAULT_MAX_SPEED;
    } else {
        return forcedMaxSpeedValue;
    }
}

void Movable::setRelativisticVelocity(bool value) {
    relativisticVelocity = value;
}



Movable::Movable() : Unit () {
}

Movable::Movable(Loadable *tmp) : Unit (tmp) {
}


void Movable::place(Vector pos, Vector vel, Vector acc, double angle) {
    Unit::place(pos, angle);
    this->vel = vel;
    this->acc = acc;
}

bool Movable::accelerateForward() {
    if(!accelerationLocked) {
        ModuleHandler *modules = getModuleHandler();
        if(modules && modules->hasModuleOfClass("engine")) {
            acc = Vector::createByAngle(getAccelerationValue(), getAngle());
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}

bool Movable::accelerateLeft() {
    if(!accelerationLocked) {
        ModuleHandler *modules = getModuleHandler();
        if(modules && modules->hasModuleOfClass("thruster")) {
            acc = Vector::createByAngle(getAccelerationValue(), getAngle() - M_PI / 2);
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}

bool Movable::accelerateRight() {
    if(!accelerationLocked) {
        ModuleHandler *modules = getModuleHandler();
        if(modules && modules->hasModuleOfClass("thruster")) {
            acc = Vector::createByAngle(getAccelerationValue(), getAngle() + M_PI / 2);
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}


void Movable::accelerateIdle() {
    if(!accelerationLocked && idleEnabled) {
    acc = vel.module() > STOP_MOVING_VELOCITY ?
        Vector::createByAngle(DEFAULT_IDLE_SPEAD, vel.angle()) :
        Vector();
    }
}

void Movable::accelerate(Vector acc) {
    if(!accelerationLocked) {
        this->acc = acc;
        accelerationLocked = true;
    }
}

Vector Movable::getVelocity() {
    return vel;
}

void Movable::updatePosition() {
    accelerateIdle();
    if(relativisticVelocity) {
        vel = vel.relativisticAddition(acc * Time::getDeltaTime(), getMaxSpeed());
    } else {
        vel += (acc * Time::getDeltaTime());
    }
    pos += (vel * Time::getDeltaTime());
    accelerationLocked = false;
}

double Movable::getReleaseSpead() {
    return root.get("release-spead", DEFAULT_RELEASE_SPEAD).asDouble();
}

void Movable::pursuit(Unit *target) {
    accelerate((target->getPosition() - getPosition() - getVelocity()) / Time::getDeltaTime());
}

void Movable::relativisticPursuit(Unit *target) {
    if(!Math::cmpd(Time::getDeltaTime(), 0.0)) {
        double velocity = target->getVelocity().module();

        if(Math::cmpd(velocity, 0)) {
            velocity = 1.0;
        } else {
            velocity = std::pow(velocity, 2);
        }

        Vector direction = target->getPosition() - getPosition();
        accelerate(direction * velocity * RELATIVISTIC_PURSUIT_COEFFICIENT / Time::getDeltaTime());
        root["max-speed"] = direction.module();
    }
}

void Movable::tick(Context *context, Event *event) {
    if(alTmpFlag != accelerationLocked) {
        if(onAcceleration(accelerationLocked)) {
            alTmpFlag = accelerationLocked;
        }
    }

    updatePosition();
    this->Unit::tick(context, event);
}
