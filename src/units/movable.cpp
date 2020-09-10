#include "movable.h"
#include <src/capabilities/modules/engine.h>
#include <math.h>
#include <src/engine/math/math.h>
#include <src/engine/context.h>
#include <src/capabilities/modulehandler.h>

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

double Movable::maxVelocity() const {
    if(!forcedMaxSpeedEnabled) {
        return loadedValues.maxVelocity;
    } else {
        return forcedMaxSpeedValue;
    }
}

void Movable::setMaxVelocity(double value) {
    loadedValues.maxVelocity = value;
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

void Movable::physicallyAttachUnit(Movable *unit) {
    m_physicallyAttachedUnits.insert(unit);
}

void Movable::physicallyDettachUnit(Movable *unit) {
    const auto it = m_physicallyAttachedUnits.find(unit);
    if(it != m_physicallyAttachedUnits.end())
        m_physicallyAttachedUnits.erase(it);
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
            //std::cout << "forward\n";
            acc = e172::Vector::createByAngle(getAccelerationValue(), angle());
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
            acc = e172::Vector::createByAngle(getAccelerationValue(), angle() - M_PI / 2);
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
            acc = e172::Vector::createByAngle(getAccelerationValue(), angle() + M_PI / 2);
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

void Movable::accelerate(e172::Vector acceleration) {
    if(!accelerationLocked) {
        this->acc = acceleration;
        accelerationLocked = true;
    }
}

e172::Vector Movable::velocity() const {
    return vel;
}

void Movable::updatePosition(e172::Context *context) {
    accelerateIdle();
    if(relativisticVelocity) {
        vel = vel.relativisticAddition(acc * context->deltaTime(), maxVelocity());
    } else {
        vel += (acc * context->deltaTime());
    }


    setRotationSpeed(std::pow(2, -vel.module() * 0.004) * DEFAULT_ROTATION_SPEED);
    pos += (vel * context->deltaTime());
    accelerationLocked = false;
}

double Movable::getReleaseSpead() const {
    return loadedValues.releaseVelocity;
}

void Movable::pursuit(e172::Context *context, Unit *target) {
    accelerate((target->position() - position() - velocity()) / context->deltaTime());
}

void Movable::relativisticPursuit(e172::Context *context, Unit *target) {
    double velocity = target->velocity().module();

    if(e172::Math::cmpf(velocity, 0)) {
        velocity = 1.0;
    } else {
        velocity = std::pow(velocity, 2);
    }

    e172::Vector direction = target->position() - position();
    if(!e172::Math::cmpf(context->deltaTime(), 0)) {
        accelerate(direction * velocity * RELATIVISTIC_PURSUIT_COEFFICIENT / context->deltaTime());
    }
    loadedValues.maxVelocity = direction.module();
}

void Movable::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(alTmpFlag != accelerationLocked) {
        if(onAcceleration(accelerationLocked)) {
            alTmpFlag = accelerationLocked;
        }
    }

    for(auto u : m_physicallyAttachedUnits) {
        pursuit(context, u);
    }

    updatePosition(context);
    this->Unit::proceed(context, eventHandler);
}

