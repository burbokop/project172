#ifndef SHIP_H
#define SHIP_H

#include "unit.h"



class WarpDrive;
class Ship : public Unit {
public:
    static constexpr double StopMovingVelocity = 1;
    static constexpr double DefaultIdleSpeed = -60;
    static constexpr double RelativisticPursuitCoefficient = 0.0025;
    static constexpr double OneWarpPoint = 9513.98639961;
private:


    double m_thrustForce = 0;
    double m_maneuverForce = 0;
    double m_maxVelocity = 0;
    double m_releaseVelocity = 0;
    double m_maxManeuverVelocity = 0;
public:
    Ship();

    bool prepareWarp();
    bool warp();
    uint8_t abortWarp(e172::Context *context);
    e172::ptr<WarpDrive> firstWarp() const;
    bool inWarp() const;

    bool thrustForward(double throtle = 1);
    void maneuverLeft();
    void maneuverRight();

    double thrustForce() const;
    void setThrustForce(double movingForce);
    double maxVelocity() const;
    void setMaxVelocity(double maxVelocity);
    double releaseVelocity() const;
    void setReleaseVelocity(double releaseVelocity);
    double maneuverForce() const;
    void setManeuverForce(double maneuverForce);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);

    double getMaxManeuverVelocity() const;
    void setMaxManeuverVelocity(double maxManeuverVelocity);
};

#endif // SHIP_H
