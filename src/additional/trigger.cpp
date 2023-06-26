#include "trigger.h"

namespace proj172::core {

void Trigger::enable() {
    enabled = true;
}

void Trigger::disanable() {
    enabled = false;
}

bool Trigger::check() {
    const bool tmp = enabled;
    enabled = false;
    return tmp;
}

} // namespace proj172::core
