#pragma once

#include "task.h"
#include <e172/math/line2d.h>
#include <e172/math/vector.h>
#include <e172/smartenum.h>

namespace proj172::core {

class Unit;
class Docker;
class DockingSession;

class DockingTask : public Task {
    e172_enum_member(
        Status, status, Idle, ApproachingToTarget, Manuevering, ApproachingToNode, WaitForDocked);

    e172::Vector<double> m_targetPoint;
    e172::Line2d m_landingStrip;
    e172::ptr<Unit> m_targetUnit;
    e172::ptr<Docker> m_docker;
    e172::ptr<DockingSession> m_session;
public:
    DockingTask(const e172::ptr<Unit> &targetUnit = nullptr);

    bool undock();

    bool approachToPoint(const e172::Vector<double> &point,
                         double cryticalDistance,
                         double speed = 1);

    e172::Vector<double> targetPoint() const { return m_targetPoint; }
    e172::Line2d landingStrip() const { return m_landingStrip; }

    // Task interface
public:
    virtual bool start(e172::Context *) override;
    virtual void proceed(e172::Context *context) override;
    virtual void initFromCommand(const std::vector<std::string> &args, e172::Context *context) override;
};

} // namespace proj172::core
