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
    static const double DEFAULT_RELEASE_SPEAD;

    double getAccelerationValue();
    static const double DEFAULT_MAX_SPEED;
    double getMaxSpeed();

    bool relativisticVelocity = true;


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
    double getReleaseSpead();


    void loop(Context *context, Event *event);
};

#endif // MOVABLE_H
