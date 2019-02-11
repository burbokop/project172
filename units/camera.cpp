#include "camera.h"

const double Camera::STOP_DISTANCE = 2;
const double Camera::MAX_SPEED_MULTIPLIER = 0.005;

Camera::Camera() : Movable () {
    target = nullptr;
}

Camera::Camera(Controller *target) : Movable () {
    this->target = target;
}


void Camera::setTarget(Controller *target) {
    this->target = target;
}

void Camera::loop(Context *context, Event *event) {


    if(target != nullptr) {

        Unit *targetUnit = target->getParent();
        if(targetUnit != nullptr) {

            Vector direction = targetUnit->getPosition() - this->pos;
            const double distance = direction.module();

            if(distance > STOP_DISTANCE) {
                Movable *movable = dynamic_cast<Movable*>(targetUnit);
                if(movable) {
                    double velocity = std::pow(movable->getVelocity().module(), 2);
                    accelerate(direction * velocity);
                    root["max-speed"] = Json::Value(distance * MAX_SPEED_MULTIPLIER);
                }
            } else {
                accelerate(Vector());
            }
        }
    }
    this->Movable::loop(context, event);
}

void Camera::render(Renderer *renderer) {
    Vector offset = renderer->getOffset();
    renderer->rect(this->pos - Vector(2, 2) + offset, this->pos + Vector(2, 2) + offset, 0x5fcf81);
}

void Camera::hit(Context *context, int value) {}
