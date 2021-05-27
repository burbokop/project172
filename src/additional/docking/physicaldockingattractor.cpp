#include "physicaldockingattractor.h"

#include <src/math/math.h>

#include <src/debug.h>

PhysicalDockingAttractor::State PhysicalDockingAttractor::state() const {
    return m_state;
}

void PhysicalDockingAttractor::setDockedRequiredProximity(const e172::PhysicalObject::Proximity &dockedRequiredProximity) {
    m_dockedRequiredProximity = dockedRequiredProximity;
}

void PhysicalDockingAttractor::setInterceptionRequiredProximity(const e172::PhysicalObject::Proximity &interceptionRequiredProximity) {
    m_interceptionRequiredProximity = interceptionRequiredProximity;
}

PhysicalDockingAttractor::PhysicalDockingAttractor() {}

void PhysicalDockingAttractor::proceed(e172::PhysicalObject::ConnectionNode node0, e172::PhysicalObject::ConnectionNode node1) {
    // TO DO add condition
    bool invert = true;

    const auto proximity = e172::PhysicalObject::nodesProximity(node0, node1, invert);
    if(m_state == NotDocked) {
        if(
                proximity.distance < m_interceptionRequiredProximity.distance
                && proximity.angle < m_interceptionRequiredProximity.angle
                ) {
            m_state = InInterception;
        }
    } else if(m_state == InInterception) {
        e172::Debug::print("node0:", node0, "node1:", node1);
        e172::PhysicalObject::dockNodes(node0, node1, 20, 2, invert);
        if(
                proximity.distance < m_dockedRequiredProximity.distance
                && proximity.angle < m_dockedRequiredProximity.angle
                ) {
            m_state = Docked;
        }

        if(
                proximity.distance > m_interceptionRequiredProximity.distance
                || proximity.angle > m_interceptionRequiredProximity.angle
                ) {
            m_state = NotDocked;
        }
    } else if(m_state == Docked) {
        e172::PhysicalObject::dockNodes(node0, node1, 20, 2, invert);
        if(
                proximity.distance > m_interceptionRequiredProximity.distance
                || proximity.angle > m_interceptionRequiredProximity.angle
                ) {
            m_state = NotDocked;
        }
    }
}
