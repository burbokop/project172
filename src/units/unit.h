#ifndef UNIT_H
#define UNIT_H

#include <src/entity.h>
#include <src/math/physicalobject.h>
#include <src/assettools/loadable.h>
#include <src/iinformative.h>
#include <src/person.h>
#include <src/utility/animator.h>
#include <src/utility/ptr.h>

class ModuleHandler;
class Docker;
class Capability;
class Unit : public e172::Entity, public e172::Loadable, public e172::PhysicalObject, public IInformative {
    double m_health = 0;
    double m_explosiveRadius = 0;
    e172::Animator m_animator;
    std::vector<e172::ptr<Capability>> m_capabilities;

    bool m_selected = false;
    uint32_t m_selectedColor;
    e172::ElapsedTimer m_selectedAnimationTimer;

    e172::ptr<Person> m_ownerPerson;
public:
    Unit();

    void addCapability(const e172::ptr<Capability> &capability);
    void removeCapability(const e172::ptr<Capability> &capability);

    template<typename T>
    e172::ptr<T> capability() const {
        for(const auto& c : m_capabilities) {
            if(const auto result = e172::smart_cast<T>(c))
                return result;
        }
        return nullptr;
    }

    template<typename T>
    std::vector<e172::ptr<Capability> > capabilities() const {
        std::vector<e172::ptr<Capability> > result;
        for(const auto& c : m_capabilities) {
            if(const auto cc = e172::smart_cast<T>(c))
                result.push_back(cc);
        }
        return result;
    }


    virtual void hit(e172::Context *context, int value);

    bool selected() const;
    double health() const;

    e172::ptr<Person> ownerPerson() const;
    void setOwnerPerson(const e172::ptr<Person> &ownerPerson);

    // IInformative interface
public:
    virtual std::string info() const override;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // UNIT_H
