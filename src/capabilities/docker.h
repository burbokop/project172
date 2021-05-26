#ifndef DOCKER_H
#define DOCKER_H


#include "capability.h"

#include <src/near.h>

#include <src/math/vector.h>

#include <src/additional/docking/dockingnodepool.h>
#include <src/additional/docking/dockingsession.h>
#include <src/additional/docking/physicaldockingattractor.h>
#include <e172/src/smartenum.h>

class Docker : public Capability {
    DockingNodePool m_nodePool;
    std::vector<e172::ptr<DockingSession>> m_sessions;
public:
    void addNode(const e172::Vector &offset, double angle);

    Docker();
    ~Docker();


    e172::ptr<DockingSession> createDockingSessionWithUnit(e172::Context *context, const e172::ptr<Unit> &unit);
    void closeAllSessions();
    size_t sessionCount() const;
    std::string sessionInfo(size_t index) const;
    e172::ptr<Unit> oppositeUnit(size_t index) const;
    bool docked(size_t index) const;

    // Entity interface
public:
    void proceed(e172::Context *, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *renderer);
};

#endif // DOCKER_H
