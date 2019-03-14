#include "camera.h"

#include "time/time.h"
#include "additional/math.h"

const double Camera::STOP_DISTANCE = 4;
const double Camera::MAX_SPEED_MULTIPLIER = 0.002 * 1000;

Camera::Camera() : Movable () {
    target = nullptr;
    //setRelativisticVelocity(false);
    place(Vector(), Vector(1, 1), Vector(), 0);
}

Camera::Camera(Controller *target) : Movable () {
    this->target = target;
    //setRelativisticVelocity(false);
    place(Vector(), Vector(1, 1), Vector(), 0);
}

void Camera::setTarget(Controller *target) {
    this->target = target;
}

void Camera::tick(Context *context, Event *event) {
    if(target) {
        if(Unit *targetUnit = target->getParent()) {
            relativisticPursuit(targetUnit);
        }
    }
    this->Movable::tick(context, event);
}

void Camera::render(Renderer *renderer) {
    Vector offset = renderer->getOffset();
    renderer->rect(this->pos - Vector(2, 2) + offset, this->pos + Vector(2, 2) + offset, 0x5fcf81);
}

void Camera::hit(Context *context, int value) {
    UNUSED(context);
    UNUSED(value);
}
