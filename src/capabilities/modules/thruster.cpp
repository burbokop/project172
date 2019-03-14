#include "thruster.h"

Thruster::Thruster() : Module () {}

Thruster::Thruster(Loadable *tmp) : Module (tmp) {}

bool Thruster::accelerateLeft() {
    if(state == READY && !root["left-thrust"].isNull()) {

    }

    return true;
}

bool Thruster::accelerateRight() {
    if(state == READY && !root["right-thrust"].isNull()) {

    }

    return true;
}

bool Thruster::isAcceleratingLeft() {
    return state == EXECUTING && !root["left-thrust"].isNull();
}

bool Thruster::isAcceleratingRight() {
    return state == EXECUTING && !root["left-thrust"].isNull();
}


