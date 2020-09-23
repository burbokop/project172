#ifndef UNIT_H
#define UNIT_H

#include <src/engine/entity.h>
#include <src/engine/physicalobject.h>
#include <src/engine/assettools/loadable.h>
#include <src/animator.h>
#include <src/iinformative.h>

class ModuleHandler;
class Docker;
class Capability;
class Unit : public e172::Entity, public e172::Loadable, public e172::PhysicalObject, public IInformative {
public:

private:
    double m_health = 0;
    double m_explosiveRadius = 0;
    Animator m_animator;
    std::vector<Capability*> m_capabilities;

    bool m_selected = false;
    uint32_t m_selectedColor;
    e172::ElapsedTimer m_selectedAnimationTimer;


public:
    Unit();

    void addCapability(Capability *capability);
    void removeCapability(Capability *capability);

    template<typename T>
    T *capability() {
        for(auto c : m_capabilities) {
            const auto cc = dynamic_cast<T*>(c);
            if(cc)
                return cc;
        }
        return nullptr;
    }

    virtual void hit(e172::Context *context, int value);

    ModuleHandler *moduleHandler() const;
    Docker *docker() const;
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
