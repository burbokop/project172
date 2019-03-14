#ifndef MOVABLE_H
#define MOVABLE_H


#include "units/unit.h"


class Movable : public Unit {
private:
    Vector vel;
    Vector acc;

    bool alTmpFlag = false;
    bool accelerationLocked = false;

    bool idleEnabled = true;

    bool forcedMaxSpeedEnabled = false;
    double forcedMaxSpeedValue = DEFAULT_MAX_SPEED;

    bool relativisticVelocity = true;
protected:
    static const double STOP_MOVING_VELOCITY;
    static const double DEFAULT_ACCELERATION_VALUE;
    static const double DEFAULT_RELEASE_SPEAD;
    static const double DEFAULT_IDLE_SPEAD;
    static const double RELATIVISTIC_PURSUIT_COEFFICIENT;


    double getAccelerationValue();
    static const double DEFAULT_MAX_SPEED;
    double getMaxSpeed();


    void setRelativisticVelocity(bool value);

    void updatePosition();

    void accelerateIdle();
    void setIdleEnabled(bool value);
    void forcedMaxSpeed(double value);
    void disableForcedMaxSpeed();

    virtual bool onAcceleration(bool start);
public:
    Movable();
    Movable(Loadable *tmp);

    void place(Vector pos, Vector vel = Vector(), Vector acc = Vector(), double angle = 0);

    void accelerate(Vector acc);
    bool accelerateForward();
    bool accelerateLeft();
    bool accelerateRight();


    Vector getVelocity();
    double getReleaseSpead();

    void pursuit(Unit *target);
    void relativisticPursuit(Unit *target);

    void tick(Context *context, Event *event);
};

#endif // MOVABLE_H
