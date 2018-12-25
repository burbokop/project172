#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "worker.h"
#include "capability.h"

class Controller : public Capability {
public:
    Controller();

    Unit *getParent();

    // Worker interface
public:
    void loop(std::vector<Worker *> *others, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // CONTROLLER_H
