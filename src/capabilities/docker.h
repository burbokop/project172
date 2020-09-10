#ifndef DOCKER_H
#define DOCKER_H


#include "capability.h"

#include <src/near.h>


class Docker : public Capability {
    Near near = Near(this, 64, 4);
private:
    enum State {
        NotDocked,
        InInterception,
        Docked
    } m_state = NotDocked;

    bool m_enabled = true;

    Unit *m_target = nullptr;
public:
    Docker();

    State state();

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
    bool enabled() const;
    void setEnabled(bool enabled);
};

#endif // DOCKER_H
