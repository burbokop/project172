#ifndef AGGRESSIVE_H
#define AGGRESSIVE_H


#include "controller.h"


class Aggressive : public Controller {
private:
    e172::ptr<Unit> m_target = nullptr;
    bool targeted = false;
    bool inWarp = false;
    e172::ElapsedTimer warpFatigueTimer = e172::ElapsedTimer(10000);

    e172::ElapsedTimer chooseTargetTimer = e172::ElapsedTimer((clock() + rand()) % 5000 + 1000);

    e172::ptr<Unit> chooseTarget(e172::Context *context);

public:
    Aggressive();

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

    // Controller interface
public:
    void onHit(e172::Context *context, int health);
};

#endif // AGGRESSIVE_H
