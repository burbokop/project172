#ifndef DOCKER_H
#define DOCKER_H


#include "capabilities/capability.h"


class Docker : public Capability {
private:

    void attach(Unit *target);

public:
    Docker();

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // DOCKER_H
