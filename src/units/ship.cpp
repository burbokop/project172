#include "ship.h"

#include "context.h"

const double Ship::ONE_WARP_POINT = 9513.98639961;

Ship::Ship() {}

bool Ship::prepareWarp() {
    WarpDrive *driveUnit = getFirstWarp();
    //for (auto val: *getModuleHandler()->getAllModules()){
    //    std::cout << "module " << val->className() << std::endl;
    //
    //}
    //std::cout << "warp" << getModuleHandler()->getAllModules() << "\n";
    if(driveUnit) {
    //    std::cout << "warp drive" << std::endl;
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

Uint8 Ship::abortWarp(Context *context) {
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

void Ship::tick(Context *context, Event *event) {
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
    this->Movable::tick(context, event);
}

bool Ship::onAcceleration(bool start) {
    WarpDrive *warp = getFirstWarp();

    if(!(warp && warp->getState() == WarpDrive::WARP_EXECUTING)) {
        return this->Movable::onAcceleration(start);
    }
    return true;
}
