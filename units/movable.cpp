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
    this->pos = pos;
    this->vel = vel;
    this->acc = acc;
    this->angle = angle;
}

void Movable::accelerateForward() {
    acc = Vector::createByAngle(getAccelerationValue(), angle);
}


void Movable::accelerateIdle() {
    acc = vel.module() > STOP_MOVING_VELOCITY ?
        Vector::createByAngle(-0.01, vel.angle()) :
                Vector();
}

Vector Movable::getVelocity() {
    return vel;
}

void Movable::updatePosition() {

    vel = vel.relativisticAddition(acc, getMaxSpeed());
    pos += vel;
}

void Movable::loop(Context *context, Event *event) {
    updatePosition();
    this->Unit::loop(context, event);
}
