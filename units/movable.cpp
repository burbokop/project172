#include "movable.h"


const double Movable::STOP_MOVING_VELOCITY = 0.015;
const double Movable::DEFAULT_ACCELERATION_VALUE = 0.1;
const double Movable::DEFAULT_RELEASE_SPEAD = 1.0;


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

double Movable::getAccelerationValue() {
    Json::Value value = root["acceleration"];
    if(value.isNumeric()) {
        return value.asDouble();
    }
    return DEFAULT_ACCELERATION_VALUE;
}

const double Movable::DEFAULT_MAX_SPEED = 2;
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
            std::vector<Module*> *engines = modules->getModulesByClass("engine");
            if(engines) {
                for(Module *module : *engines) {
                    module->animate(Animator::LOOP, Animator::NOTRENDER);
                }
            }
            acc = Vector::createByAngle(getAccelerationValue(), getAngle());
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}


void Movable::accelerateIdle() {
    if(!accelerationLocked && idleEnabled) {
    acc = vel.module() > STOP_MOVING_VELOCITY ?
        Vector::createByAngle(-0.01, vel.angle()) :
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
        vel = vel.relativisticAddition(acc, getMaxSpeed());
    } else {
        vel += acc;
    }
    pos += vel;
    accelerationLocked = false;
}

double Movable::getReleaseSpead() {
    return root.get("release-spead", DEFAULT_RELEASE_SPEAD).asDouble();
}

void Movable::loop(Context *context, Event *event) {
    updatePosition();
    this->Unit::loop(context, event);
}
