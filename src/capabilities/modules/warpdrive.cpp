#include "warpdrive.h"
#include "context.h"
#include "additional/stringformer.h"


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

std::string WarpDrive::getStateAsString() {
    switch (warpState) {
    case WARP_DISABLED:
        return "WARP_DISABLED";
    case WARP_LOADING:
        return "WARP_LOADING";
    case WARP_READY:
        return "WARP_READY";
    case WARP_EXECUTING:
        return "WARP_EXECUTING";
    case WARP_RECHARGING:
        return "WARP_RECHARGING";
    default:
        return std::to_string(warpState);
    }
}

std::string WarpDrive::getStateAsIcon() {
    switch (warpState) {
    case WARP_DISABLED:
        return "disabled";
    case WARP_LOADING:
        return ">>";
    case WARP_READY:
        return "ready";
    case WARP_EXECUTING:
        return "=>";
    case WARP_RECHARGING:
        return "<<";
    default:
        return std::to_string(warpState);
    }
}

double WarpDrive::getCharging() {
    return (static_cast<double>(currentChargindIteration) / chargindIterations);
}

std::string WarpDrive::getInfo() {
    std::string chargingBar;
    if(warpState == WarpDrive::WARP_RECHARGING) {
        chargingBar = StringFormer::line(static_cast<unsigned int>((1 - getCharging()) * 4));
    } else if (warpState == WarpDrive::WARP_LOADING) {
        chargingBar = StringFormer::line(static_cast<unsigned int>((timer.ready() * 4)));
    } else if (warpState == WarpDrive::WARP_DISABLED) {
        chargingBar = "";
    } else if (warpState == WarpDrive::WARP_EXECUTING) {
        chargingBar = "----";
    } else if (warpState == WarpDrive::WARP_READY) {
        chargingBar = "----";
    }
    return "WD   |" + chargingBar + "|   " + getStateAsIcon();
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
        audioPlayer.play();
        animator.play(Animator::LOOP);
        return true;
    }
    return false;
}

Uint8 WarpDrive::abortWarp(Context* context) {
    Uint8 result = warpState;
    if(warpState == WARP_EXECUTING) {
        context->addEvent(parent, Context::SPAWN_ENGINE_EXPLOSIVE, 16);
        audioPlayer.stop();
        animator.play(Animator::NOTRENDER);
    }
    if(warpState == WARP_EXECUTING || warpState == WARP_READY || warpState == WARP_LOADING) warpState = WARP_RECHARGING;
    return result;
}

#include <iostream>
void WarpDrive::loop(Context *context, Event *event) {
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
