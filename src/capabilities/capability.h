#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "worker.h"

class Unit;

class Capability : public Worker {
    Unit *m_parent = nullptr;
public:
    virtual bool setParent(Unit *parent);
    virtual void unsetParent();
    Unit *parent() const;
};

#endif // COMPONENTS_H
