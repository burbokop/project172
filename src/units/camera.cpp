#include "camera.h"

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

void Camera::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(target) {
        if(Unit *targetUnit = target->parentUnit()) {
            relativisticPursuit(context, targetUnit);
        }
    }
    this->Movable::proceed(context, eventHandler);
}

void Camera::render(e172::AbstractRenderer *renderer) {
    if(r_cam.isNull()) {
        r_cam = renderer->detachCamera();
    }

    uint32_t color = 0x5fcf81;
    if(r_cam.isNull()) {
        color = 0xff0000;
    } else {
        r_cam.setPosition(pos);
    }

    e172::Vector offset = renderer->offset();
    if(m_i++ % 100 > 50 && r_cam.isNull()) {
        renderer->drawCircle(pos + offset, 2, color);
    } else {
        renderer->drawSquare(pos + offset, 2, color);
    }
}

void Camera::hit(e172::Context *, int) {}
