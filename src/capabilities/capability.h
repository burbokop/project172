#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <src/entity.h>
#include <src/assettools/loadable.h>
#include <src/utility/ptr.h>

class Unit;

class Capability : public e172::Entity, public e172::Loadable {
    e172::ptr<Unit> m_parentUnit;
public:
    virtual bool setParentUnit(const e172::ptr<Unit> &parent);
    e172::ptr<Unit> parentUnit() const;
};

#endif // COMPONENTS_H
