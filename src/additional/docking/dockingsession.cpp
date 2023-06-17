#include "dockingsession.h"

#include <src/context.h>
#include <src/debug.h>
#include <src/math/math.h>
#include <src/graphics/abstractrenderer.h>
#include <src/units/unit.h>

namespace proj172::core {

void DockingSession::release() {
    --m_usagesCount;
}

bool DockingSession::docked() {
    return m_physicalDockingAttractor.state() == PhysicalDockingAttractor::Docked;
}

DockingSession::DockingSession(e172::FactoryMeta &&meta, Private)
    : e172::Entity(std::move(meta))
{
    m_physicalDockingAttractor.setInterceptionRequiredProximity({64, e172::Math::Pi / 8});
    m_physicalDockingAttractor.setDockedRequiredProximity({2, e172::Math::Pi / 64});
}

std::array<e172::ptr<Unit>, 2> DockingSession::units() const {
    return {m_item0.unit, m_item1.unit};
}

std::map<e172::ptr<Unit>, DockingNodePool::Node> DockingSession::nodes() const {
    return {{m_item0.unit, m_item0.node}, {m_item1.unit, m_item1.node}};
}

e172::ptr<Unit> DockingSession::oppositeUnit(const e172::ptr<const Unit> &unit) const
{
    if (m_item0.unit == unit) {
        return m_item1.unit;
    } else if (m_item1.unit == unit) {
        return m_item0.unit;
    }
    return nullptr;
}

PhysicalDockingAttractor::State DockingSession::state() const {
    return m_physicalDockingAttractor.state();
}

e172::ptr<DockingSession> DockingSession::createSession(DockingNodePool *pull0, DockingNodePool *pull1, const e172::ptr<Unit> &unit0, const e172::ptr<Unit> &unit1) {
    const auto node0 = pull0->nextFreeNode();
    const auto node1 = pull1->nextFreeNode();
    if(node0.isValid() && node1.isValid()) {
        auto result = e172::FactoryMeta::make<DockingSession>(Private{});
        result->m_item0.pool = pull0;
        result->m_item1.pool = pull1;
        result->m_item0.node = node0;
        result->m_item1.node = node1;
        result->m_item0.physicalNode = unit0->connectionNode(node0.offset(), node0.angle());
        result->m_item1.physicalNode = unit1->connectionNode(node1.offset(), node1.angle());
        result->m_item0.unit = unit0;
        result->m_item1.unit = unit1;
        return result;
    }
    return nullptr;
}

DockingSession::~DockingSession() {
    m_item0.pool->returnToPool(m_item0.node);
    m_item1.pool->returnToPool(m_item1.node);
}

void DockingSession::proceed(e172::Context *context, e172::EventHandler *) {
    const auto lastState = m_physicalDockingAttractor.state();
    m_physicalDockingAttractor.proceed(m_item0.physicalNode, m_item1.physicalNode);
    if (m_physicalDockingAttractor.state() == PhysicalDockingAttractor::NotDocked
        && lastState == PhysicalDockingAttractor::Docked) {
        if (!m_selfReleased) {
            release();
            m_selfReleased = true;
        }
    }

    if(!fullUsageCount()) {
        if (!m_selfReleased) {
            release();
            m_selfReleased = true;
        }
    }

    if(m_usagesCount <= 0) {
        context->emitMessage(e172::Context::DestroyEntity, entityId());
    }
}

void DockingSession::render(e172::AbstractRenderer *renderer) {
    if (m_physicalDockingAttractor.state() == PhysicalDockingAttractor::InInterception) {
        renderer->drawLineShifted(m_item0.physicalNode.position(),
                                  m_item0.physicalNode.center(),
                                  0xffff00);

        renderer->drawLineShifted(m_item1.physicalNode.position(),
                                  m_item1.physicalNode.center(),
                                  0xffff00);
    } else if (m_physicalDockingAttractor.state() == PhysicalDockingAttractor::Docked) {
        renderer->drawLineShifted(m_item0.physicalNode.center(),
                                  m_item1.physicalNode.center(),
                                  0x00ff00);
    } else {
        renderer->drawLineShifted(m_item0.physicalNode.center(),
                                  m_item1.physicalNode.center(),
                                  e172::randomColor(e172::Random::uniq()));
    }
}

bool DockingSession::fullUsageCount() const {
    return m_usagesCount >= 3;
}

} // namespace proj172::core
