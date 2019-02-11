#include "ship.h"


const double Ship::ONE_WARP_POINT = 95.1398639961;


Ship::Ship() {
}

Ship::Ship(Loadable *tmp) : Movable (tmp) {
}

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
        if(success) forcedMaxSpeed(driveUnit->getSpeadUnit() * ONE_WARP_POINT);
        return success;
    }
    return false;
}

Uint8 Ship::abortWarp() {
    WarpDrive *driveUnit = getFirstWarp();
    if(driveUnit) {
        bool success = driveUnit->abortWarp();
        if(success) disableForcedMaxSpeed();
        return success;
    }
    return false;
}

WarpDrive *Ship::getFirstWarp() {
    ModuleHandler *modules = getModuleHandler();
    if(modules) {
        std::vector<Module*> *drives = modules->getModulesByClass("warp-drive");
        if(drives) {
            return dynamic_cast<WarpDrive*>(drives->at(0));
        }
    }
    return nullptr;
}

void Ship::loop(Context *context, Event *event) {
    ModuleHandler *modules = getModuleHandler();
    if(modules) {
        std::vector<Module*> *drives = modules->getModulesByClass("warp-drive");
        if(drives) {
            WarpDrive *driveUnit = dynamic_cast<WarpDrive*>(drives->at(0));
            if(driveUnit) {
                if(driveUnit->getState() == WarpDrive::WARP_EXECUTING) {
                    accelerateForward();
                }
            }
        }
    }


    this->Movable::loop(context, event);
}


//DEPRECATED
void Ship::render(Renderer *renderer) {
    this->Movable::render(renderer);

    /* maybi will return in future versions
    int health = root.get("health", 1).asInt();
    int healthMax = root.get("health-max", 80).asInt();
    Vector offset = renderer->getOffset();
    renderer->rect(pos + offset + Vector(-21, -23), pos + offset + Vector(21, -19), 0xFFA773);
    renderer->rect(pos + offset + Vector(-21, -23), pos + offset + Vector(-19 + health * 40 / healthMax, -19), 0xB2F63D);
    */
}
//-----------

