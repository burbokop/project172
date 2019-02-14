#ifndef AGGRESSIVE_H
#define AGGRESSIVE_H

#include "controller.h"

class Aggressive : public Controller {
public:
    Aggressive();

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer);

    // Controller interface
public:
    void onHit(Context *context, int health);
};

#endif // AGGRESSIVE_H
