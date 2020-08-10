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

void Docker::tick(Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(context);
    UNUSED(eventHandler);
    if(state == IN_INTERCEPTION) {
        double dst = (parent()->getPosition() - target->getPosition()).module();
        if(dst < 64) {
            state = ATTRACTED;
        }
    } else if(state == ATTRACTED) {
        double dst = (parent()->getPosition() - target->getPosition()).module();
        double dstAngle = target->getAngle();
        if(dst < 4 && parent()->isOnAngle(dstAngle)) {
            attach(target);
        }
        parent()->rotateToAngle(dstAngle);
        Movable *movableParent = dynamic_cast<Movable*>(parent());
        if(movableParent) {
            movableParent->place(parent()->getPosition(), (target->getPosition() - parent()->getPosition()) / 100, e172::Vector(), parent()->getAngle());
        }
    } else if(state == DOCKED) {
        parent()->place(target->getPosition(), target->getAngle());
    }
}

void Docker::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}
