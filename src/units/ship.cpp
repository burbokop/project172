#include "ship.h"

const double Ship::ONE_WARP_POINT = 9513.98639961;

Ship::Ship() {}

bool Ship::prepareWarp() {
    WarpDrive *driveUnit = getFirstWarp();
    if(driveUnit) {
        bool success = driveUnit->prepareWarp();
        return success;
    }
    return false;
}

bool Ship::warp() {
    WarpDrive *driveUnit = getFirstWarp();
    if(driveUnit) {
        bool success = driveUnit->warp();
        if(success) {
            forcedMaxSpeed(driveUnit->getSpeadUnit() * ONE_WARP_POINT);
        }
        return success;
    }
    return false;
}

uint8_t Ship::abortWarp(e172::Context *context) {
    WarpDrive *driveUnit = getFirstWarp();
    if(driveUnit) {
        bool success = driveUnit->abortWarp(context);
        if(success) {
            disableForcedMaxSpeed();
        }
        return success;
    }
    return false;
}

WarpDrive *Ship::getFirstWarp() {
    ModuleHandler *modules = getModuleHandler();
    if(modules) {
        std::vector<Module*> *drives = modules->getModulesByClass("WarpDrive");
        if(drives) {
            return dynamic_cast<WarpDrive*>(drives->at(0));
        }
    }
    return nullptr;
}

void Ship::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    ModuleHandler *modules = getModuleHandler();
    if(modules) {
        std::vector<Module*> *drives = modules->getModulesByClass("WarpDrive");
        if(drives) {
            WarpDrive *driveUnit = dynamic_cast<WarpDrive*>(drives->at(0));
            if(driveUnit) {
                if(driveUnit->getState() == WarpDrive::WARP_EXECUTING) {

                    accelerateForward();
                }
            }
        }
    }
    this->Movable::proceed(context, eventHandler);
}

bool Ship::onAcceleration(bool start) {
    WarpDrive *warp = getFirstWarp();

    if(!(warp && warp->getState() == WarpDrive::WARP_EXECUTING)) {
        return this->Movable::onAcceleration(start);
    }
    return true;
}
