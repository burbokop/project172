#ifndef DOCKINGSESSION_H
#define DOCKINGSESSION_H

#include "dockingnodepool.h"
#include "physicaldockingattractor.h"
#include <src/engine/entity.h>
#include <src/engine/physicalobject.h>


class DockingSession : public e172::Entity {
    struct Item {
        DockingNodePool *pool = nullptr;
        DockingNodePool::Node node;
        e172::PhysicalObject::ConnectionNode physicalNode;
    };
    Item item0;
    Item item1;
    int m_usagesCount = 3;
    bool selfReleased = false;
    PhysicalDockingAttractor physicalDockingAttractor;
    DockingSession();

    PhysicalDockingAttractor::State state() const;
public:

    static DockingSession *createSession(DockingNodePool *pull0, DockingNodePool *pull1, e172::PhysicalObject *object0, e172::PhysicalObject *object1);

    ~DockingSession();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
    bool fullUsageCount() const;
    void release();
};

#endif // DOCKINGSESSION_H
