#pragma once

#include "../additional/docking/dockingnodepool.h"
#include "../additional/docking/dockingsession.h"
#include "../near.h"
#include "capability.h"
#include <e172/math/vector.h>
#include <e172/smartenum.h>

namespace proj172::core {

class Docker : public Capability {
    DockingNodePool m_nodePool;
    std::vector<e172::ptr<DockingSession>> m_sessions;
public:
    void addNode(const e172::Vector<double> &offset, double angle);

    Docker(e172::FactoryMeta &&meta);
    ~Docker();


    e172::ptr<DockingSession> createDockingSessionWithUnit(e172::Context *context, const e172::ptr<Unit> &unit);
    void closeAllSessions();
    size_t sessionCount() const;
    std::string sessionInfo(size_t index) const;
    e172::ptr<Unit> oppositeUnit(size_t index) const;
    bool docked(size_t index) const;

    // Entity interface
public:
    void proceed(e172::Context *, e172::EventHandler *);
    void render(e172::Context *context, e172::AbstractRenderer *renderer);
};

} // namespace proj172::core

