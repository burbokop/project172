#ifndef DOCKINGSESSION_H
#define DOCKINGSESSION_H

#include "dockingnodepool.h"
#include "physicaldockingattractor.h"
#include <src/engine/entity.h>
#include <src/engine/physicalobject.h>

class Unit;
class DockingSession : public e172::Entity {
    struct Item {
        DockingNodePool *pool = nullptr;
        DockingNodePool::Node node;
        e172::PhysicalObject::ConnectionNode physicalNode;
        Unit *unit = nullptr;
    };
    Item item0;
    Item item1;
    int m_usagesCount = 3;
    bool selfReleased = false;
    PhysicalDockingAttractor physicalDockingAttractor;
    DockingSession();
public:
    std::array<Unit*, 2> units() const;
    Unit *oppositeUnit(Unit *unit) const;
    PhysicalDockingAttractor::State state() const;

    bool fullUsageCount() const;
    void release();

    static DockingSession *createSession(DockingNodePool *pull0, DockingNodePool *pull1, Unit *unit0, Unit *unit1);

    ~DockingSession();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // DOCKINGSESSION_H
