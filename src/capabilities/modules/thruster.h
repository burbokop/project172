#ifndef THRUSTER_H
#define THRUSTER_H

#include "capabilities/modules/module.h"

class Thruster : public Module {
    bool leftThrust = false;
    bool rightThrust = false;
private:
    enum State {
        DISABLED,
        READY,
        EXECUTING,
        RECHARGING
    } state = DISABLED;

public:
    Thruster();
    Thruster(Loadable *tmp);

    bool accelerateLeft();
    bool accelerateRight();

    bool isAcceleratingLeft();
    bool isAcceleratingRight();

};

#endif // THRUSTER_H
