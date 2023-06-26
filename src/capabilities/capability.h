#pragma once

#include <src/entity.h>
#include <src/assettools/loadable.h>
#include <src/utility/ptr.h>

namespace proj172::core {

class Unit;

class Capability : public e172::Entity, public e172::Loadable {
public:
    Capability(e172::FactoryMeta &&meta)
        : e172::Entity(std::move(meta))
    {
    }

    e172::ptr<Unit> parentUnit() { return m_parentUnit; }
    e172::ptr<const Unit> parentUnit() const { return m_parentUnit; }

    virtual bool setParentUnit(const e172::ptr<Unit> &parent);

private:
    e172::ptr<Unit> m_parentUnit;
};

} // namespace proj172::core
