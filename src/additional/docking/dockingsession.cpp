#include "dockingsession.h"

#include <src/context.h>
#include <src/debug.h>

#include <src/math/math.h>

#include <src/graphics/abstractrenderer.h>

#include <src/units/unit.h>


void DockingSession::release() {
    --m_usagesCount;
}

bool DockingSession::docked() {
    return physicalDockingAttractor.state() == PhysicalDockingAttractor::Docked;
}

DockingSession::DockingSession() {
    physicalDockingAttractor.setInterceptionRequiredProximity({ 64, e172::Math::Pi / 8 });
    physicalDockingAttractor.setDockedRequiredProximity({ 2, e172::Math::Pi / 64 });
}

std::array<e172::ptr<Unit>, 2> DockingSession::units() const {
    return { item0.unit, item1.unit };
}

std::map<e172::ptr<Unit>, DockingNodePool::Node> DockingSession::nodes() const {
    return { { item0.unit, item0.node }, { item1.unit, item1.node } };
}

e172::ptr<Unit> DockingSession::oppositeUnit(const e172::ptr<Unit> &unit) const {
    if(item0.unit == unit) {
        return item1.unit;
    } else if(item1.unit == unit) {
        return item0.unit;
    }
    return nullptr;
}

PhysicalDockingAttractor::State DockingSession::state() const {
    return physicalDockingAttractor.state();
}

e172::ptr<DockingSession> DockingSession::createSession(DockingNodePool *pull0, DockingNodePool *pull1, const e172::ptr<Unit> &unit0, const e172::ptr<Unit> &unit1) {
    const auto node0 = pull0->nextFreeNode();
    const auto node1 = pull1->nextFreeNode();
    if(node0.isValid() && node1.isValid()) {
        auto result = new DockingSession();
        result->item0.pool = pull0;
        result->item1.pool = pull1;
        result->item0.node = node0;
        result->item1.node = node1;
        result->item0.physicalNode = unit0->connectionNode(node0.offset(), node0.angle());
        result->item1.physicalNode = unit1->connectionNode(node1.offset(), node1.angle());
        result->item0.unit = unit0;
        result->item1.unit = unit1;
        return result;
    }
    return nullptr;
}

DockingSession::~DockingSession() {
    item0.pool->returnToPool(item0.node);
    item1.pool->returnToPool(item1.node);
}

void DockingSession::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    const auto lastState = physicalDockingAttractor.state();
    physicalDockingAttractor.proceed(item0.physicalNode, item1.physicalNode);    
    if(physicalDockingAttractor.state() == PhysicalDockingAttractor::NotDocked && lastState == PhysicalDockingAttractor::Docked) {
        if(!selfReleased) {
            release();
            selfReleased = true;
        }
    }

    if(!fullUsageCount()) {
        if(!selfReleased) {
            release();
            selfReleased = true;
        }
    }

    if(m_usagesCount <= 0) {
        context->emitMessage(e172::Context::DESTROY_ENTITY, entityId());
    }
}

void DockingSession::render(e172::AbstractRenderer *renderer) {
    if(physicalDockingAttractor.state() == PhysicalDockingAttractor::InInterception) {
        renderer->drawLineShifted(item0.physicalNode.position(), item0.physicalNode.center(), 0xffff00);
        renderer->drawLineShifted(item1.physicalNode.position(), item1.physicalNode.center(), 0xffff00);
    } else if(physicalDockingAttractor.state() == PhysicalDockingAttractor::Docked) {
        renderer->drawLineShifted(item0.physicalNode.center(), item1.physicalNode.center(), 0x00ff00);
    } else {
        renderer->drawLineShifted(item0.physicalNode.center(), item1.physicalNode.center(), e172::randomColor());
    }
}

bool DockingSession::fullUsageCount() const {
    return m_usagesCount >= 3;
}
