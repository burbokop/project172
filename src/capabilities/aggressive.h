#ifndef AGGRESSIVE_H
#define AGGRESSIVE_H


#include "capabilities/controller.h"


class Aggressive : public Controller {
private:
    std::vector<Worker*> *targets = nullptr;
    Unit *target = nullptr;
    bool targeted = false;
    bool inWarp = false;
    Trigger stopWarpTrigger = Trigger();
    Timer warpFatigueTimer = Timer(10000);


    Unit *chooseTarget();

public:
    Aggressive(std::vector<Worker*> *units);

    // Worker interface
public:
    void tick(Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

    // Controller interface
public:
    void onHit(Context *context, int health);
};

#endif // AGGRESSIVE_H
