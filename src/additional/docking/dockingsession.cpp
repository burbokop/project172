#include "dockingsession.h"

#include <src/engine/context.h>

#include <src/engine/math/math.h>

#include <src/engine/graphics/abstractrenderer.h>


void DockingSession::release() {
    --m_usagesCount;
}

DockingSession::DockingSession() {
    physicalDockingAttractor.setInterceptionRequiredProximity({ 64, e172::Math::Pi / 8 });
    physicalDockingAttractor.setDockedRequiredProximity({ 2, e172::Math::Pi / 64 });
}

PhysicalDockingAttractor::State DockingSession::state() const {
    return physicalDockingAttractor.state();
}

DockingSession *DockingSession::createSession(DockingNodePool *pull0, DockingNodePool *pull1, e172::PhysicalObject *object0, e172::PhysicalObject *object1) {
    const auto node0 = pull0->nextFreeNode();
    const auto node1 = pull1->nextFreeNode();
    if(node0.isValid() && node1.isValid()) {
        auto result = new DockingSession();
        result->item0.pool = pull0;
        result->item1.pool = pull1;
        result->item0.node = node0;
        result->item1.node = node1;
        result->item0.physicalNode = object0->connectionNode(node0.offset(), node0.angle());
        result->item1.physicalNode = object1->connectionNode(node1.offset(), node1.angle());
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
