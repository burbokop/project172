#ifndef AGGRESSIVE_H
#define AGGRESSIVE_H


#include "controller.h"


class Aggressive : public Controller {
private:
    std::list<Entity*> targets;
    Unit *target = nullptr;
    bool targeted = false;
    bool inWarp = false;
    Trigger stopWarpTrigger = Trigger();
    e172::ElapsedTimer warpFatigueTimer = e172::ElapsedTimer(10000);


    Unit *chooseTarget();

public:
    Aggressive(std::list<Entity*> units);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

    // Controller interface
public:
    void onHit(e172::Context *context, int health);
};

#endif // AGGRESSIVE_H
