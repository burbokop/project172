#include "trigger.h"

Trigger::Trigger() {

}

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
