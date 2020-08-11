#ifndef DOCKER_H
#define DOCKER_H


#include "capabilities/capability.h"


class Docker : public Capability {
private:
    enum State {
        NOT_DOCKED,
        IN_INTERCEPTION,
        ATTRACTED,
        DOCKED
    } state = NOT_DOCKED;

    Unit *target = nullptr;

    void attach(Unit *target);

public:
    Docker();

    void dock(Unit *target);
    void undock();
    State getState();

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // DOCKER_H
