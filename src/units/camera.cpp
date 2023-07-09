#include "camera.h"

#include "../units/unit.h"
#include <e172/context.h>
#include <e172/math/math.h>

namespace proj172::core {

const double Camera::STOP_DISTANCE = 4;
const double Camera::MAX_SPEED_MULTIPLIER = 0.002 * 1000;

e172::ptr<Controller> Camera::target() const {
    return m_target;
}

Camera::Camera(e172::FactoryMeta &&meta, const e172::ptr<Controller> &target)
    : e172::Entity(std::move(meta))
    , m_target(target)
{
    addTag("C");
}

void Camera::setTarget(const e172::ptr<Controller> &target) {
    m_target = target;
}

void Camera::proceed(e172::Context *context, e172::EventHandler *) {
    if(m_target) {
        if(const auto targetUnit = m_target->parentUnit()) {
            //addRestoringForce(targetUnit->position());

            const auto f = [](double x, double x0) {
                if(x0 != e172::Math::null) {
                    const auto a = (1 - x / x0);
                    if(a != e172::Math::null) {
                        return x * std::abs(1 / a - 1) * 2;
                    }
                }
                return 0.;
            };

            //const auto f = [](double x, double x0){
            //    return std::sqrt(x) * x * 0.5;
            //};

            //const auto f = [](double x, double x0){
            //    return std::pow(2, x) - 1;
            //};


            if((targetUnit->position() - position()).cheapModule() / 2 > 200) {
                resetPhysicsProperties(targetUnit->position(), 0);
            } else {
                addDistanceRelatedForce(targetUnit->position(), f, 200);
            }
            //addFollowForce(targetUnit->position(), 200);
            //relativisticPursuit(context, targetUnit);
        }
    }
    proceedPhysics(context->deltaTime());
}

void Camera::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
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

    //if(target()) {
    //    renderer->drawString(std::to_string((position() - target()->parentUnit()->position()).x()), position() + offset + e172::Vector(20, 20), color);
    //    renderer->drawString(std::to_string((position() - target()->parentUnit()->position()).y()), position() + offset + e172::Vector(20, 40), color);
    //}
}

} // namespace proj172::core
