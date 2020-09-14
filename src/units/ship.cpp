#include "ship.h"


#include <src/capabilities/modules/engine.h>
#include <src/capabilities/modules/warpdrive.h>
#include <src/capabilities/modulehandler.h>


double Ship::thrustForce() const {
    return m_thrustForce;
}

void Ship::setThrustForce(double movingForce) {
    m_thrustForce = movingForce;
}

double Ship::maxVelocity() const {
    return m_maxVelocity;
}

void Ship::setMaxVelocity(double maxVelocity) {
    m_maxVelocity = maxVelocity;
}

double Ship::releaseVelocity() const {
    return m_releaseVelocity;
}

void Ship::setReleaseVelocity(double releaseVelocity) {
    m_releaseVelocity = releaseVelocity;
}

double Ship::maneuverForce() const {
    return m_maneuverForce;
}

void Ship::setManeuverForce(double maneuverForce) {
    m_maneuverForce = maneuverForce;
}

double Ship::getMaxManeuverVelocity() const {
    return m_maxManeuverVelocity;
}

void Ship::setMaxManeuverVelocity(double maxManeuverVelocity) {
    m_maxManeuverVelocity = maxManeuverVelocity;
}

Ship::Ship() {
    registerInitFunction([this]() {
        m_thrustForce = asset<double>("thrust_force", 2);
        m_maxVelocity = asset<double>("max_velocity", 120);
        m_releaseVelocity = asset<double>("release_velocity", 1);
        m_maneuverForce = asset<double>("maneuver_force", 1);
        m_maxManeuverVelocity = asset<double>("maneuver_velocity", 4);
    });
}

bool Ship::prepareWarp() {
    if(const auto driveUnit = firstWarp()) {
        return driveUnit->prepareWarp();
    }
    return false;
}

bool Ship::warp() {
    if(const auto driveUnit = firstWarp()) {
        return driveUnit->warp();
    }
    return false;
}

uint8_t Ship::abortWarp(e172::Context *context) {
    if(const auto driveUnit = firstWarp()) {
        return driveUnit->abortWarp(context);
    }
    return false;
}

bool Ship::thrustForward() {
    const auto mh = moduleHandler();
    if(mh) {
        const auto engines = mh->modulesOfClass("Engine");
        bool ok = false;
        if(engines.size() > 0) {
            for(auto module : engines) {
                Engine *engine = dynamic_cast<Engine*>(module);
                if(engine && engine->forward()) {
                    ok = true;
                }
            }

            if(ok) {
                addLimitedForwardForce(m_thrustForce, m_maxVelocity);
                return true;
            }
        }
    }
    return false;
}

void Ship::maneuverLeft() {
    addLimitedRotationForce(-m_maneuverForce, m_maxManeuverVelocity);
}

void Ship::maneuverRight() {
    addLimitedRotationForce(m_maneuverForce, m_maxManeuverVelocity);
}

WarpDrive *Ship::firstWarp() {
    ModuleHandler *modules = moduleHandler();
    if(modules) {
        const auto drives = modules->modulesOfClass("WarpDrive");
        if(drives.size() > 0) {
            return dynamic_cast<WarpDrive*>(drives.at(0));
        }
    }
    return nullptr;
}

void Ship::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    ModuleHandler *modules = moduleHandler();
    if(modules) {
        const auto drives = modules->modulesOfClass("WarpDrive");
        if(drives.size() > 0) {
            WarpDrive *driveUnit = dynamic_cast<WarpDrive*>(drives.at(0));
            if(driveUnit) {
                if(driveUnit->getState() == WarpDrive::WARP_EXECUTING) {
                    addLimitedForwardForce(m_thrustForce, OneWarpPoint);
                }
            }
        }
    }
    Unit::proceed(context, eventHandler);
}

//bool Ship::onAcceleration(bool start) {
//    WarpDrive *warp = getFirstWarp();
//
//    if(!(warp && warp->getState() == WarpDrive::WARP_EXECUTING)) {
//        return this->Movable::onAcceleration(start);
//    }
//    return true;
//}
