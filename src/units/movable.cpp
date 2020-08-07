#include "movable.h"
#include "capabilities/modules/engine.h"
#include "context.h"
#include "time/time.h"
#include <math.h>
#include <engine/math/math.h>

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

double Movable::getAccelerationValue() {
    return loadedValues.acceleration;
}

double Movable::getMaxSpeed() const {
    if(!forcedMaxSpeedEnabled) {
        return loadedValues.maxVelocity;
    } else {
        return forcedMaxSpeedValue;
    }
}

void Movable::setRelativisticVelocity(bool value) {
    relativisticVelocity = value;
}



Movable::Movable() : Unit () {
    registerInitFunction([this]() {
        loadedValues.acceleration = asset<double>("acceleration", DEFAULT_ACCELERATION_VALUE);
        loadedValues.maxVelocity = asset<double>("max-speed", DEFAULT_MAX_SPEED);
        loadedValues.releaseVelocity = asset<double>("releaseVelocity", DEFAULT_RELEASE_SPEAD);
    });
}

void Movable::place(e172::Vector pos, e172::Vector vel, e172::Vector acc, double angle) {
    Unit::place(pos, angle);
    this->vel = vel;
    this->acc = acc;
}

bool Movable::accelerateForward() {
    if(!accelerationLocked) {
        ModuleHandler *modules = getModuleHandler();
        if(modules && modules->hasModuleOfClass("Engine")) {
            std::cout << "forward\n";
            acc = e172::Vector::createByAngle(getAccelerationValue(), getAngle());
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}

bool Movable::accelerateLeft() {
    if(!accelerationLocked) {
        ModuleHandler *modules = getModuleHandler();
        if(modules && modules->hasModuleOfClass("Thruster")) {
            acc = e172::Vector::createByAngle(getAccelerationValue(), getAngle() - M_PI / 2);
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}

bool Movable::accelerateRight() {
    if(!accelerationLocked) {
        ModuleHandler *modules = getModuleHandler();
        if(modules && modules->hasModuleOfClass("Thruster")) {
            acc = e172::Vector::createByAngle(getAccelerationValue(), getAngle() + M_PI / 2);
            accelerationLocked = true;
            return true;
        }
    }
    return false;
}


void Movable::accelerateIdle() {
    if(!accelerationLocked && idleEnabled) {
    acc = vel.module() > STOP_MOVING_VELOCITY ?
        e172::Vector::createByAngle(DEFAULT_IDLE_SPEAD, vel.angle()) :
        e172::Vector();
    }
}

void Movable::accelerate(e172::Vector acc) {
    if(!accelerationLocked) {
        this->acc = acc;
        accelerationLocked = true;
    }
}

e172::Vector Movable::getVelocity() {
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

double Movable::getReleaseSpead() const {
    return loadedValues.releaseVelocity;
}

void Movable::pursuit(Unit *target) {
    accelerate((target->getPosition() - getPosition() - getVelocity()) / Time::getDeltaTime());
}

void Movable::relativisticPursuit(Unit *target) {
    if(!e172::Math::cmpd(Time::getDeltaTime(), 0.0)) {
        double velocity = target->getVelocity().module();

        if(e172::Math::cmpd(velocity, 0)) {
            velocity = 1.0;
        } else {
            velocity = std::pow(velocity, 2);
        }

        e172::Vector direction = target->getPosition() - getPosition();
        accelerate(direction * velocity * RELATIVISTIC_PURSUIT_COEFFICIENT / Time::getDeltaTime());
        loadedValues.maxVelocity = direction.module();
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

