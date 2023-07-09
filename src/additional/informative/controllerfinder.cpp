#include "controllerfinder.h"

#include "../../units/unit.h"

namespace proj172::core {

ControllerFinder::ControllerFinder(Controller *p1, Controller *p2) {
    this->p1 = p1;
    this->p2 = p2;
}

std::string ControllerFinder::info() const {
    double value = (
        p2->parentUnit()->position() - p1->parentUnit()->position()
    ).angle() - p1->parentUnit()->rotation();

    return std::to_string(
        static_cast<int>(
            std::abs(value * 10)
        )
    );
}

} // namespace proj172::core
