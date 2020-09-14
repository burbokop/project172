#ifndef UNIT_H
#define UNIT_H

#include <src/engine/entity.h>
#include <src/engine/physicalobject.h>
#include <src/engine/assettools/loadable.h>
#include <src/animator.h>
#include <src/iinformative.h>

class ModuleHandler;
class Docker;
class Capability;
class Unit : public e172::Entity, public e172::Loadable, public e172::PhysicalObject, public IInformative {
public:
    static constexpr double DefaultMaxRotationSpeed = 0.0014 * 1000;
    static constexpr double StopMovingVelocity = 1;
    static constexpr double DefaultAccelerationValue = 120;
    static constexpr double DefaultReleaseSpead = 1;
    static constexpr double DefaultMaxSpeed = 120;
    static constexpr double DefaultIdleSpead = - 60;
    static constexpr double RelativisticPursuitCoefficient = 0.0025;

private:
    double m_health = 0;
    double m_explosiveRadius = 0;
    Animator m_animator;
    std::vector<Capability*> m_capabilities;

    bool m_selected = false;
    uint32_t m_selectedColor;
    e172::ElapsedTimer m_selectedAnimationTimer;

    double m_movingForce = 0;
    double m_maxVelocity = 0;
    double m_releaseVelocity = 0;
    double m_maxRotationVelocity = 1;
public:
    Unit();

    void addCapability(Capability *capability);
    void removeCapability(Capability *capability);

    virtual void hit(e172::Context *context, int value);


    ModuleHandler *moduleHandler() const;
    Docker *docker() const;
    bool selected() const;
    double health() const;
    double movingForce() const;
    double maxVelocity() const;
    double releaseVelocity() const;
    void setMovingForce(double movingForce);
    void setMaxVelocity(double maxVelocity);
    void setReleaseVelocity(double releaseVelocity);
    double maxRotationVelocity() const;
    void setMaxRotationVelocity(double maxRotationVelocity);


    // IInformative interface
public:
    virtual std::string info() const override;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // UNIT_H
