#ifndef DOCKINGTASKEXECUTOR_H
#define DOCKINGTASKEXECUTOR_H

#include <src/math/line2d.h>
#include <src/math/vector.h>

#include <src/units/ship.h>

#include <src/additional/docking/dockingsession.h>

#include <src/smartenum.h>

class DockingTaskExecutor {
    E172_SMART_ENUM_MEMBER(Status, status,
                           Idle,
                           ApproachingToTarget,
                           Manuevering,
                           ApproachingToNode,
                           WaitForDocked,
                           Docked,
                           )

    e172::Vector m_targetPoint;
    e172::Line2d m_landingStrip;
    e172::ptr<Capability> m_capability;
    e172::ptr<Unit> m_targetUnit;
    e172::ptr<Docker> m_docker;
    e172::ptr<DockingSession> m_session;
public:
    DockingTaskExecutor(const e172::ptr<Capability>& capability);

    bool start(const e172::ptr<Unit> &targetUnit);
    bool undock();

    bool approachToPoint(const e172::Vector& point, double cryticalDistance, double speed = 1);

    void proceed(e172::Context *context);

    e172::Vector targetPoint() const;
    e172::Line2d landingStrip() const;
};

#endif // DOCKINGTASKEXECUTOR_H
