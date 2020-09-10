#include "warpdrive.h"


#include <src/additional/stringformer.h>
#include <src/engine/args.h>
#include <src/engine/context.h>
#include <src/units/unit.h>

const uint8_t WarpDrive::WARP_DISABLED = 0;
const uint8_t WarpDrive::WARP_LOADING = 1;
const uint8_t WarpDrive::WARP_READY = 2;
const uint8_t WarpDrive::WARP_EXECUTING = 3;
const uint8_t WarpDrive::WARP_RECHARGING = 4;



WarpDrive::WarpDrive() {
    registerInitFunction([this](){
        warpVelocity = asset<double>("warp-speed", 0.1);
    });
}

int WarpDrive::getState() {
    return warpState;
}

std::string WarpDrive::stateAsString() const {
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

std::string WarpDrive::stateAsIcon() const {
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

double WarpDrive::charging() const {
    return (static_cast<double>(currentChargindIteration) / chargindIterations);
}

std::string WarpDrive::info() const {
    std::string chargingBar;
    if(warpState == WarpDrive::WARP_RECHARGING) {
        chargingBar = StringFormer::line(static_cast<unsigned int>((1 - charging()) * 4));
    } else if (warpState == WarpDrive::WARP_LOADING) {
        chargingBar = StringFormer::line(static_cast<unsigned int>((timer.progress() * 4)));
    } else if (warpState == WarpDrive::WARP_DISABLED) {
        chargingBar = "";
    } else if (warpState == WarpDrive::WARP_EXECUTING) {
        chargingBar = "----";
    } else if (warpState == WarpDrive::WARP_READY) {
        chargingBar = "----";
    }
    return "WD   |" + chargingBar + "|   " + stateAsIcon();
}

double WarpDrive::getSpeadUnit() const {
    return warpVelocity;
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
        animator.play(Animator::Loop);
        return true;
    }
    return false;
}

uint8_t WarpDrive::abortWarp(e172::Context* context) {
    uint8_t result = warpState;
    if(warpState == WARP_EXECUTING) {
        const e172::Args args(parentUnit()->position(), parentUnit()->velocity() * 0.8, 16);
        context->emitMessage(e172::Context::SPAWN_EXPLOSIVE, args);
        audioPlayer.stop();
        animator.play(Animator::NotRender);
    }
    if(warpState == WARP_EXECUTING || warpState == WARP_READY || warpState == WARP_LOADING) warpState = WARP_RECHARGING;
    return result;
}

void WarpDrive::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(warpState == WARP_LOADING) {
        if(timer.check()) {
            warpState = WARP_READY;
        }
    } else if(warpState == WARP_RECHARGING) {
        if(timer.check()) {
            currentChargindIteration++;
            if(currentChargindIteration >= chargindIterations) {
                currentChargindIteration = 0;
                warpState = WARP_DISABLED;
            }
        }
    }

    this->Module::proceed(context, eventHandler);
}

