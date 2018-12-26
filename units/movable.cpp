#include "movable.h"


const double Movable::STOP_MOVING_VELOCITY = 0.015;
const double Movable::DEFAULT_ACCELERATION_VALUE = 0.1;
double Movable::getAccelerationValue() {
    Json::Value value = root["acceleration"];
    if(value.isNumeric()) {
        return value.asDouble();
    }
    return DEFAULT_ACCELERATION_VALUE;
}

const double Movable::DEFAULT_MAX_SPEED = 2;
double Movable::getMaxSpeed() {
    Json::Value value = root["max-speed"];
    if(value.isNumeric()) {
        return value.asDouble();
    }
    return DEFAULT_MAX_SPEED;
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
    if(!accelerationLocked) {
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
    vel = vel.relativisticAddition(acc, getMaxSpeed());
    pos += vel;
    accelerationLocked = false;
}

void Movable::loop(Context *context, Event *event) {
    updatePosition();
    this->Unit::loop(context, event);
}
