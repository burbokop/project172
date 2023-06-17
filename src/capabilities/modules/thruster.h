#ifndef THRUSTER_H
#define THRUSTER_H

#include "module.h"

namespace proj172::core {

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
    Thruster(e172::FactoryMeta &&meta);
    Thruster(Loadable *tmp);

    bool accelerateLeft();
    bool accelerateRight();

    bool isAcceleratingLeft();
    bool isAcceleratingRight();

};

} // namespace proj172::core

#endif // THRUSTER_H
