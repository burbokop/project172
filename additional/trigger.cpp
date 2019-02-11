#include "trigger.h"

Trigger::Trigger() {

}

void Trigger::enable() {
    enabled = true;
}

bool Trigger::check() {
    const bool tmp = enabled;
    enabled = false;
    return tmp;
}
