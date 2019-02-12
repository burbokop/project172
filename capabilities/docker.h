#ifndef DOCKER_H
#define DOCKER_H

#include "capability.h"

class Docker : public Capability {
public:
    Docker();

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // DOCKER_H
