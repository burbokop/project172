#ifndef MOVABLE_H
#define MOVABLE_H

#include "units/unit.h"

class Movable : public Unit {
protected:
    static const double STOP_MOVING_VELOCITY;
    static const double DEFAULT_ACCELERATION_VALUE;
    double getAccelerationValue();
    static const double DEFAULT_MAX_SPEED;
    double getMaxSpeed();


    Vector vel;
    Vector acc;

    void updatePosition();

public:
    Movable();
    Movable(Loadable *tmp);



    void place(Vector pos, Vector vel = Vector(), Vector acc = Vector(), double angle = 0);

    void accelerateForward();
    void accelerateIdle();

    Vector getVelocity();

    void loop(Context *context, Event *event);
};

#endif // MOVABLE_H
