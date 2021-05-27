#ifndef DOCKINGTASK_H
#define DOCKINGTASK_H

#include "task.h"

#include <src/math/line2d.h>
#include <src/math/vector.h>

#include <src/units/ship.h>

#include <src/additional/docking/dockingsession.h>

#include <src/smartenum.h>

class DockingTask : public Task {
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
    e172::ptr<Unit> m_targetUnit;
    e172::ptr<Docker> m_docker;
    e172::ptr<DockingSession> m_session;
public:
    DockingTask(const e172::ptr<Unit> &targetUnit);

    bool undock();

    bool approachToPoint(const e172::Vector& point, double cryticalDistance, double speed = 1);


    e172::Vector targetPoint() const;
    e172::Line2d landingStrip() const;

    // Task interface
public:
    virtual bool start(e172::Context *) override;
    virtual void proceed(e172::Context *context) override;
};

#endif // DOCKINGTASK_H
