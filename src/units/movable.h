#ifndef MOVABLE_H
#define MOVABLE_H


#include "units/unit.h"


class Movable : public Unit {
private:
    e172::Vector vel;
    e172::Vector acc;

    bool alTmpFlag = false;
    bool accelerationLocked = false;

    bool idleEnabled = true;

    bool forcedMaxSpeedEnabled = false;
    double forcedMaxSpeedValue = DEFAULT_MAX_SPEED;

    bool relativisticVelocity = true;

    struct {
        double acceleration;
        double maxVelocity;
        double releaseVelocity;
    } loadedValues;
protected:
    static const double STOP_MOVING_VELOCITY;
    static const double DEFAULT_ACCELERATION_VALUE;
    static const double DEFAULT_RELEASE_SPEAD;
    static const double DEFAULT_IDLE_SPEAD;
    static const double RELATIVISTIC_PURSUIT_COEFFICIENT;


    double getAccelerationValue();
    static const double DEFAULT_MAX_SPEED;
    double getMaxSpeed() const;


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

    void place(e172::Vector pos, e172::Vector vel = e172::Vector(), e172::Vector acc = e172::Vector(), double angle = 0);

    void accelerate(e172::Vector acc);
    bool accelerateForward();
    bool accelerateLeft();
    bool accelerateRight();


    e172::Vector getVelocity();
    double getReleaseSpead() const;

    void pursuit(Unit *target);
    void relativisticPursuit(Unit *target);

    void tick(Context *context, e172::AbstractEventHandler *eventHandler);
};

#endif // MOVABLE_H
