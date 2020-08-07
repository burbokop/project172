#include "thruster.h"

Thruster::Thruster() : Module () {
    registerInitFunction([this](){
        leftThrust = asset<double>("left-thrust", false);
        leftThrust = asset<double>("right-thrust", false);
    });
}

bool Thruster::accelerateLeft() {
    if(state == READY && leftThrust) {

    }

    return true;
}

bool Thruster::accelerateRight() {
    if(state == READY && rightThrust) {

    }

    return true;
}

bool Thruster::isAcceleratingLeft() {
    return state == EXECUTING && leftThrust;
}

bool Thruster::isAcceleratingRight() {
    return state == EXECUTING && rightThrust;
}


