#include "camera.h"

#include "time/time.h"

const double Camera::STOP_DISTANCE = 4;
const double Camera::MAX_SPEED_MULTIPLIER = 0.002 * 1000;

Camera::Camera() : Movable () {
    target = nullptr;
    //setRelativisticVelocity(false);
    place(e172::Vector(), e172::Vector(1, 1), e172::Vector(), 0);
}

Camera::Camera(Controller *target) : Movable () {
    this->target = target;
    //setRelativisticVelocity(false);
    place(e172::Vector(), e172::Vector(1, 1), e172::Vector(), 0);
}

void Camera::setTarget(Controller *target) {
    this->target = target;
}

void Camera::tick(Context *context, Event *event) {
    if(target) {
        if(Unit *targetUnit = target->parent()) {
            relativisticPursuit(targetUnit);
        }
    }
    this->Movable::tick(context, event);
}

void Camera::render(e172::AbstractRenderer *renderer) {
    e172::Vector offset = renderer->offset();
    renderer->drawRect(this->pos - e172::Vector(2, 2) + offset, this->pos + e172::Vector(2, 2) + offset, 0x5fcf81);
}

void Camera::hit(Context *context, int value) {
    UNUSED(context);
    UNUSED(value);
}
