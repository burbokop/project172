#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "worker.h"

class Unit;

class Capability : public Worker
{
protected:
    Unit *parent = nullptr;
public:
    bool setParent(Unit *parent);
    void unsetParent();
};

#endif // COMPONENTS_H
