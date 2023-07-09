#include "ship.h"

#include "../capabilities/modulehandler.h"
#include "../capabilities/modules/engine.h"
#include "../capabilities/modules/warpdrive.h"
#include <e172/math/math.h>

namespace proj172::core {

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

Ship::Ship(e172::FactoryMeta &&meta)
    : Unit(std::move(meta))
{
    registerInitFunction([this]() {
        m_thrustForce = asset<double>("thrust_force", 120);
        m_maxVelocity = asset<double>("max_velocity", 120);
        m_releaseVelocity = asset<double>("release_velocity", 1);
        m_maneuverForce = asset<double>("maneuver_force", 4);
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

bool Ship::thrustForward(double throtle) {
    if(const auto mh = capability<ModuleHandler>()) {
        const auto engines = mh->modules<Engine>();
        bool ok = false;
        if(engines.size() > 0) {
            for (const auto &module : engines) {
                const auto engine = e172::smart_cast<Engine>(module);
                if(engine && engine->forward()) {
                    ok = true;
                }
            }

            if(ok) {
                throtle = std::min(throtle, 1.);
                addLimitedForwardForce(m_thrustForce * throtle, m_maxVelocity * throtle);
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

e172::ptr<WarpDrive> Ship::firstWarp() const {
    if(const auto modules = capability<ModuleHandler>()) {
        const auto drives = modules->modules<WarpDrive>();
        if(drives.size() > 0) {
            return e172::smart_cast<WarpDrive>(drives.at(0));
        }
    }
    return nullptr;
}

bool Ship::inWarp() const {
    if(const auto driveUnit = firstWarp()) {
        return driveUnit->warpState() == WarpDrive::WarpExecuting;
    }
    return false;
}

void Ship::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    if(const auto modules = capability<ModuleHandler>()) {
        const auto drives = modules->modules<WarpDrive>();
        if(drives.size() > 0) {
            if (const auto driveUnit = e172::smart_cast<WarpDrive>(drives.at(0))) {
                if (driveUnit->warpState() == WarpDrive::WarpExecuting) {
                    addLimitedForwardForce(m_thrustForce, OneWarpPoint);
                    blockFrictionPerTick();
                    //addForwardForce(m_thrustForce);
                    addDistanceRelatedRotationForce(velocity().angle(), [](double x, double){ return x * x; }, 0, 100);
                    //addRotationRestoringForce(velocity().angle(), 10);
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

} // namespace proj172::core
