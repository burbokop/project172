#include "warpdrive.h"


const Uint8 WarpDrive::WARP_DISABLED = 0;
const Uint8 WarpDrive::WARP_LOADING = 1;
const Uint8 WarpDrive::WARP_READY = 2;
const Uint8 WarpDrive::WARP_EXECUTING = 3;
const Uint8 WarpDrive::WARP_RECHARGING = 4;



WarpDrive::WarpDrive() {
}

WarpDrive::WarpDrive(Loadable *tmp) : Module (tmp) {
}

int WarpDrive::getState() {
    return warpState;
}

double WarpDrive::getSpeadUnit() {
    return  root.get("warp-speed", 0.1).asDouble();
}

bool WarpDrive::prepareWarp() {
    if(warpState == WARP_DISABLED) {
        warpState = WARP_LOADING;
        timer.reset();
        return true;
    }
    return false;
}

bool WarpDrive::warp() {
    if(warpState == WARP_READY) {
        warpState = WARP_EXECUTING;
        return true;
    }
    return false;
}

Uint8 WarpDrive::abortWarp() {
    Uint8 result = warpState;
    if(warpState == WARP_EXECUTING || warpState == WARP_READY || warpState == WARP_LOADING) warpState = WARP_RECHARGING;
    return result;
}

#include <iostream>
void WarpDrive::loop(Context *context, Event *event) {

    std::cout << "it: " << currentChargindIteration << " warp state: ";
    switch (warpState) {
    case WARP_DISABLED:
        std::cout << "WARP_DISABLED";
        break;
    case WARP_LOADING:
        std::cout << "WARP_LOADING";
        break;
    case WARP_READY:
        std::cout << "WARP_READY";
        break;
    case WARP_EXECUTING:
        std::cout << "WARP_EXECUTING";
        break;
    case WARP_RECHARGING:
        std::cout << "WARP_RECHARGING";
        break;
    default:
        break;
    }
    std::cout << "\n";


    if(warpState == WARP_LOADING) {
        if(timer.count(true)) {
            warpState = WARP_READY;
        }
    } else if(warpState == WARP_RECHARGING) {
        if(timer.count(true)) {
            currentChargindIteration++;
            if(currentChargindIteration >= chargindIterations) {
                currentChargindIteration = 0;
                warpState = WARP_DISABLED;
            }
        }
    }

    this->Module::loop(context, event);
}
