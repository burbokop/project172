#ifndef MOVABLE_H
#define MOVABLE_H

#include "units/unit.h"

class Movable : public Unit {
private:
    Vector vel;
    Vector acc;
    bool accelerationLocked = false;
    bool idleEnabled = true;

    bool forcedMaxSpeedEnabled = false;
    double forcedMaxSpeedValue = DEFAULT_MAX_SPEED;
protected:
    static const double STOP_MOVING_VELOCITY;
    static const double DEFAULT_ACCELERATION_VALUE;
    double getAccelerationValue();
    static const double DEFAULT_MAX_SPEED;
    double getMaxSpeed();


    void updatePosition();

    void accelerateIdle();
    void accelerate(Vector acc);
    void setIdleEnabled(bool value);
    void forcedMaxSpeed(double value);
    void disableForcedMaxSpeed();
public:
    Movable();
    Movable(Loadable *tmp);



    void place(Vector pos, Vector vel = Vector(), Vector acc = Vector(), double angle = 0);

    bool accelerateForward();


    Vector getVelocity();

    void loop(Context *context, Event *event);
};

#endif // MOVABLE_H
