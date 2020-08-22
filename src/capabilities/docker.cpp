#include "docker.h"
#include "units/unit.h"
#include "units/movable.h"

Docker::Docker() {
}

void Docker::attach(Unit *target) {
    if(target && state == ATTRACTED) {
        state = DOCKED;
    }
}

void Docker::dock(Unit *target) {
    if(target && state == NOT_DOCKED) {
        state = IN_INTERCEPTION;
        this->target = target;
    }
}

void Docker::undock() {
    if(state == DOCKED) {
        state = NOT_DOCKED;
    }
}

Docker::State Docker::getState() {
    return state;
}

void Docker::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(context);
    UNUSED(eventHandler);
    if(state == IN_INTERCEPTION) {
        double dst = (parentUnit()->getPosition() - target->getPosition()).module();
        if(dst < 64) {
            state = ATTRACTED;
        }
    } else if(state == ATTRACTED) {
        double dst = (parentUnit()->getPosition() - target->getPosition()).module();
        double dstAngle = target->getAngle();
        if(dst < 4 && parentUnit()->isOnAngle(context, dstAngle)) {
            attach(target);
        }
        parentUnit()->rotateToAngle(context, dstAngle);
        Movable *movableParent = dynamic_cast<Movable*>(parentUnit());
        if(movableParent) {
            movableParent->place(parentUnit()->getPosition(), (target->getPosition() - parentUnit()->getPosition()) / 100, e172::Vector(), parentUnit()->getAngle());
        }
    } else if(state == DOCKED) {
        parentUnit()->place(target->getPosition(), target->getAngle());
    }
}

void Docker::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}
