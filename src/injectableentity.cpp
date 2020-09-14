#include "injectableentity.h"


std::vector<Capability *> InjectableEntity::capabilities() const {
    return m_capabilities;
}

void InjectableEntity::addCapability(const Capability *capability) {

}

void InjectableEntity::removeCapability(const Capability *capability) {

}

void InjectableEntity::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {

}
