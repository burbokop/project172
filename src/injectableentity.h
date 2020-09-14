#ifndef INJECTABLEENTITY_H
#define INJECTABLEENTITY_H

#include <src/engine/entity.h>

class Capability;
class InjectableEntity : public e172::Entity {
    std::vector<Capability*> m_capabilities;
public:
    InjectableEntity();
    std::vector<Capability *> capabilities() const;
    void addCapability(const Capability *capability);
    void removeCapability(const Capability *capability);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
};

#endif // INJECTABLEENTITY_H
