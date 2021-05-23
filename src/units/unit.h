#ifndef UNIT_H
#define UNIT_H

#include <src/entity.h>
#include <src/math/physicalobject.h>
#include <src/assettools/loadable.h>
#include <src/iinformative.h>
#include <src/utility/animator.h>
#include <src/utility/ptr.h>

class ModuleHandler;
class Docker;
class Capability;
class Unit : public e172::Entity, public e172::Loadable, public e172::PhysicalObject, public IInformative {
public:

private:
    double m_health = 0;
    double m_explosiveRadius = 0;
    e172::Animator m_animator;
    std::vector<e172::ptr<Capability>> m_capabilities;

    bool m_selected = false;
    uint32_t m_selectedColor;
    e172::ElapsedTimer m_selectedAnimationTimer;
public:
    Unit();

    void addCapability(const e172::ptr<Capability> &capability);
    void removeCapability(const e172::ptr<Capability> &capability);

    template<typename T>
    e172::ptr<T> capability() {
        for(auto c : m_capabilities) {
            if(const auto result = e172::smart_cast<T>(c))
                return result;
        }
        return nullptr;
    }

    virtual void hit(e172::Context *context, int value);

    e172::ptr<ModuleHandler> moduleHandler() const;
    e172::ptr<Docker> docker() const;
    bool selected() const;
    double health() const;

    // IInformative interface
public:
    virtual std::string info() const override;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // UNIT_H
