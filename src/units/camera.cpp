#include "camera.h"

#include <src/engine/context.h>
#include <src/engine/objectregistry.h>
#include <src/units/unit.h>
#include <math.h>

const double Camera::STOP_DISTANCE = 4;
const double Camera::MAX_SPEED_MULTIPLIER = 0.002 * 1000;

Controller *Camera::target() const {
    return m_target;
}

Camera::Camera(Controller *target) {
    m_target = target;
    addTag("C");
}

void Camera::setTarget(Controller *target) {
    m_target = target;
}

void Camera::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    if(m_target) {
        if(Unit *targetUnit = m_target->parentUnit()) {
            if(targetUnit == e172::Alive) {
                //addRestoringForce(targetUnit->position());

                const auto f = [](double x, double x0){
                    return std::sqrt(x) * x * 0.5;
                };


                addDistanceRelatedForce(targetUnit->position(), f, 0);
                //addFollowForce(targetUnit->position(), 200);
                //relativisticPursuit(context, targetUnit);
            }
        }
    }
    proceedPhysics(context->deltaTime());
}

void Camera::render(e172::AbstractRenderer *renderer) {
    if(r_cam.isNull()) {
        r_cam = renderer->detachCamera();
    }

    uint32_t color = 0x5fcf81;
    if(r_cam.isNull()) {
        color = 0xff0000;
    } else {
        r_cam.setPosition(position());
    }

    e172::Vector offset = renderer->offset();
    if(m_i++ % 100 > 50 && r_cam.isNull()) {
        renderer->drawCircle(position() + offset, 2, color);
    } else {
        renderer->drawSquare(position() + offset, 2, color);
    }
}
