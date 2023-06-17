#include "__capability.h"
#include "injectableentity.h"

#include <algorithm>

InjectableEntity::InjectableEntity(e172::FactoryMeta &&meta)
    : e172::Entity(std::move(meta))
{
    __installEUF({[](e172::Entity *e, e172::Context *c, e172::EventHandler *h) {
                      const auto capabilities = e->cast<InjectableEntity>()->m_capabilities;
                      for (const auto &capability : capabilities) {
                          capability->proceed(c, h);
                      }
                  },
                  [](e172::Entity *e, e172::AbstractRenderer *r) {
                      const auto capabilities = e->cast<InjectableEntity>()->m_capabilities;
                      for (const auto &capability : capabilities) {
                          capability->render(r);
                      }
                  }});
}

bool InjectableEntity::addCapability(__Capability *capability) {
    if(capability) {
        if(!capability->m_parentEntity) {
            capability->m_parentEntity = this;
            m_capabilities.push_back(capability);
            return true;
        }
    }
    return false;
}

bool InjectableEntity::removeCapability(__Capability *capability) {
    if(capability) {
        const auto it = std::find(m_capabilities.begin(), m_capabilities.end(), capability);
        if(it != m_capabilities.end()) {
            capability->m_parentEntity = nullptr;
            m_capabilities.erase(it);
            return true;
        }
    }
    return false;
}
