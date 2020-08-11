#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <engine/entity.h>



class Unit;

class Capability : public e172::Entity {
    Unit *m_parent = nullptr;
public:
    virtual bool setParent(Unit *parent);
    virtual void unsetParent();
    Unit *parent() const;
};

#endif // COMPONENTS_H
