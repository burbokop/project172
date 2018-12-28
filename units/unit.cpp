#include "unit.h"

const double Unit::DEFAULT_ROTATION_SPEED = 0.02;

double Unit::getRotationSpeed() {
    return DEFAULT_ROTATION_SPEED;
}

Unit::Unit() : Loadable () {
}

Unit::Unit(Loadable *tmp) {
    tmp->clone(this);
}

void Unit::place(Vector pos, double angle) {
    this->pos = pos;
    this->angle = angle;
}


void Unit::addCapability(Capability *capability) {
    if(capability->setParent(this)) {
        capabilities.push_back(capability);
    }
}

void Unit::removeCapability(Capability *capability) {
    std::vector<Capability*>::iterator pos = std::find(capabilities.begin(), capabilities.end(), capability);
    if(pos != capabilities.end()) {
        capability->unsetParent();
        capabilities.erase(pos);
    }
}

ModuleHandler *Unit::getModuleHandler() {
    for(Capability *cap : capabilities) {
        ModuleHandler* mh = dynamic_cast<ModuleHandler*>(cap);
        if(mh != nullptr) {
            return  mh;
        }
    }
    return nullptr;
}

void Unit::rotateLeft() {
    angle -= getRotationSpeed();
}

void Unit::rotateRight() {
    angle += getRotationSpeed();
}

void Unit::lockAngle(double angle) {
    angleLocked = true;
    dstAngle = angle;
}

void Unit::unlockAngle() {
    angleLocked = false;
}

Vector Unit::getPosition() {
    return pos;
}

double Unit::getAngle() {
    return angle;
}

void Unit::loop(Context *context, Event *event) {
    const double rotationSpeed = getRotationSpeed();
    if(angleLocked && std::abs(angle - dstAngle) > rotationSpeed * 5) {
        if(angle > dstAngle) angle -= rotationSpeed;
        else angle += rotationSpeed;
    }

    for(Capability *cap : capabilities) {
        cap->loop(context, event);
    }
}

void Unit::render(Renderer *renderer, Vector offset) {
    this->animator.setAngle(angle);
    this->animator.setPosition(pos);
    this->animator.render(renderer, offset);
    for(Capability *cap : capabilities) {
        cap->render(renderer, offset);
    }
}
