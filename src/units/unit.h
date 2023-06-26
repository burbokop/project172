#pragma once

#include "src/graphics/color.h"
#include "src/utility/signal.h"
#include <src/assettools/loadable.h>
#include <src/entity.h>
#include <src/iinformative.h>
#include <src/math/physicalobject.h>
#include <src/persons/person.h>
#include <src/utility/animator.h>
#include <src/utility/ptr.h>

namespace proj172::core {

class ModuleHandler;
class Docker;
class Capability;

class Unit : public e172::Entity,
             public e172::Loadable,
             public e172::PhysicalObject,
             public Informative
{
    struct Private
    {};

public:
    Unit(e172::FactoryMeta &&meta);

    void addCapability(const e172::ptr<Capability> &capability);
    void addCapability(std::unique_ptr<Capability> &&capability);
    void removeCapability(const e172::ptr<Capability> &capability);

    auto &capabilityAdded() { return m_capabilityAdded; };
    auto &capabilityRemoved() { return m_capabilityRemoved; }

    template<typename T>
    e172::ptr<T> capability() const
    {
        for(const auto& c : m_capabilities) {
            if(const auto result = e172::smart_cast<T>(c))
                return result;
        }
        return nullptr;
    }

    std::vector<e172::ptr<Capability>> capabilities() const { return m_capabilities; }

    template<typename T>
    std::vector<e172::ptr<T>> capabilities() const
    {
        std::vector<e172::ptr<T>> result;
        result.reserve(m_capabilities.size());
        for(const auto& c : m_capabilities) {
            if(const auto cc = e172::smart_cast<T>(c))
                result.push_back(cc);
        }
        return result;
    }

    virtual void hit(e172::Context *context, int value);

    bool selected() const { return m_selected; }
    double health() const { return m_health; }

    e172::ptr<Person> ownerPerson() const { return m_ownerPerson; }
    void setOwnerPerson(const e172::ptr<Person> &ownerPerson) { m_ownerPerson = ownerPerson; }

    ~Unit();

    // IInformative interface
public:
    virtual std::string info() const override;

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
    void writeNet(e172::WriteBuffer &buf) override;
    bool readNet(e172::ReadBuffer &&buf) override;
    bool needSyncNet() const override;

private:
    double m_health = 0;
    double m_explosiveRadius = 0;
    e172::Animator m_animator;
    std::vector<e172::ptr<Capability>> m_capabilities;
    bool m_selected = false;
    e172::Color m_selectedColor;
    e172::ElapsedTimer m_selectedAnimationTimer;
    e172::ptr<Person> m_ownerPerson;
    e172::Signal<void(e172::ptr<Capability>), Private> m_capabilityAdded;
    e172::Signal<void(e172::Entity::Id), Private> m_capabilityRemoved;
};

} // namespace proj172::core
