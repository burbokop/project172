#pragma once

#include "dockingnodepool.h"
#include "physicaldockingattractor.h"
#include <e172/entity.h>
#include <e172/math/physicalobject.h>
#include <e172/utility/ptr.h>

namespace proj172::core {

class Unit;
class DockingSession : public e172::Entity {
    struct Private
    {};

public:
    std::array<e172::ptr<Unit>, 2> units() const;
    std::map<e172::ptr<Unit>, DockingNodePool::Node> nodes() const;
    e172::ptr<Unit> oppositeUnit(const e172::ptr<const Unit> &unit) const;
    PhysicalDockingAttractor::State state() const;

    bool fullUsageCount() const;
    void release();
    bool docked();

    static e172::ptr<DockingSession> createSession(DockingNodePool *pull0,
                                                   DockingNodePool *pull1,
                                                   const e172::ptr<Unit> &unit0,
                                                   const e172::ptr<Unit> &unit1);

    DockingSession(e172::FactoryMeta &&meta, Private);
    ~DockingSession();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;

private:
    struct Item
    {
        DockingNodePool *pool = nullptr;
        DockingNodePool::Node node;
        e172::PhysicalObject::ConnectionNode physicalNode;
        e172::ptr<Unit> unit;
    };

private:
    Item m_item0;
    Item m_item1;
    int m_usagesCount = 3;
    bool m_selfReleased = false;
    PhysicalDockingAttractor m_physicalDockingAttractor;
};

} // namespace proj172::core
