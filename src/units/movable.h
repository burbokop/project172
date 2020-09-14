#ifndef MOVABLE_H
#define MOVABLE_H

#include "unit.h"


class Movable : public Unit {
    bool accelerationLocked = false;
    bool idleEnabled = true;
    bool forcedMaxSpeedEnabled = false;
    double forcedMaxSpeedValue = DefaultMaxSpeed;
    bool relativisticVelocity = true;
protected:
    void setRelativisticVelocity(bool value);

    void accelerateIdle();
    void setIdleEnabled(bool value);
    void forcedMaxSpeed(double value);
    void disableForcedMaxSpeed();

    virtual bool onAcceleration(bool start);
public:
    Movable();
    Movable(Loadable *tmp);

    void accelerate(e172::Vector acceleration);
    bool accelerateForward();
    bool accelerateLeft();
    bool accelerateRight();

    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
};

#endif // MOVABLE_H
