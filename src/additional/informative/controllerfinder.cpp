#include "controllerfinder.h"

ControllerFinder::ControllerFinder(Controller *p1, Controller *p2) {
    this->p1 = p1;
    this->p2 = p2;
}

std::string ControllerFinder::getInfo() {
    double value = (
        p2->parent()->getPosition() - p1->parent()->getPosition()
    ).angle() - p1->parent()->getAngle();

    return std::to_string(
        static_cast<int>(
            std::abs(value * 10)
        )
    );
}
