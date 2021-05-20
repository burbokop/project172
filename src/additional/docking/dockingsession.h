#ifndef DOCKINGSESSION_H
#define DOCKINGSESSION_H

#include "dockingnodepool.h"
#include "physicaldockingattractor.h"
#include <src/entity.h>
#include <src/physicalobject.h>
#include <src/utility/ptr.h>

class Unit;
class DockingSession : public e172::Entity {
    struct Item {
        DockingNodePool *pool = nullptr;
        DockingNodePool::Node node;
        e172::PhysicalObject::ConnectionNode physicalNode;
        e172::ptr<Unit> unit;
    };
    Item item0;
    Item item1;
    int m_usagesCount = 3;
    bool selfReleased = false;
    PhysicalDockingAttractor physicalDockingAttractor;
    DockingSession();
public:
    std::array<e172::ptr<Unit>, 2> units() const;
    std::map<e172::ptr<Unit>, DockingNodePool::Node> nodes() const;
    e172::ptr<Unit> oppositeUnit(const e172::ptr<Unit> &unit) const;
    PhysicalDockingAttractor::State state() const;

    bool fullUsageCount() const;
    void release();

    static e172::ptr<DockingSession> createSession(DockingNodePool *pull0, DockingNodePool *pull1, const e172::ptr<Unit> &unit0, const e172::ptr<Unit> &unit1);

    ~DockingSession();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // DOCKINGSESSION_H
