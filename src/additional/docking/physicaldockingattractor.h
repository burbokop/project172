#pragma once

#include <src/math/physicalobject.h>

namespace proj172::core {

class PhysicalDockingAttractor {
public:
    enum State {
        NotDocked,
        InInterception,
        Docked
    };
private:
    State m_state = NotDocked;

    e172::PhysicalObject::Proximity m_dockedRequiredProximity;
    e172::PhysicalObject::Proximity m_interceptionRequiredProximity;

public:
    PhysicalDockingAttractor();
    void proceed(e172::PhysicalObject::ConnectionNode node0, e172::PhysicalObject::ConnectionNode node1);
    State state() const;

    void setDockedRequiredProximity(const e172::PhysicalObject::Proximity &dockedRequiredProximity);
    void setInterceptionRequiredProximity(const e172::PhysicalObject::Proximity &interceptionRequiredProximity);
};

} // namespace proj172::core
