#ifndef PHYSICALDOCKINGATTRACTOR_H
#define PHYSICALDOCKINGATTRACTOR_H

#include <src/physicalobject.h>



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

#endif // PHYSICALDOCKINGATTRACTOR_H
