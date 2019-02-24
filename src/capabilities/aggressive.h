#ifndef AGGRESSIVE_H
#define AGGRESSIVE_H


#include "capabilities/controller.h"


class Aggressive : public Controller {
private:
    static const double ANGLE_DELTA;


    std::vector<Worker*> *targets = nullptr;
    Unit *target = nullptr;
    bool targeted = false;
    Trigger stopWarpTrigger = Trigger();
    Timer warpFatigueTimer = Timer(30000);


    Unit *chooseTarget();

public:
    Aggressive(std::vector<Worker*> *units);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer);

    // Controller interface
public:
    void onHit(Context *context, int health);
};

#endif // AGGRESSIVE_H
