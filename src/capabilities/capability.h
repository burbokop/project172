#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <engine/entity.h>



class Unit;

class Capability : public e172::Entity {
    Unit *m_parentUnit = nullptr;
public:
    virtual bool setParentUnit(Unit *parent);
    virtual void unsetParentUnit();
    Unit *parentUnit() const;
};

#endif // COMPONENTS_H
