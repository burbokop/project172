#pragma once

#include "__capability.h"
#include <e172/entity.h>
#include <list>

class InjectableEntity : public e172::Entity {
    std::list<__Capability*> m_capabilities;
public:
    InjectableEntity(e172::FactoryMeta &&meta);
    bool addCapability(__Capability *capability);
    bool removeCapability(__Capability *capability);

    template<typename T>
    std::list<T*> capabilities() {
        std::list<T*> result;
        for(auto c : m_capabilities) {
            if(c->instanceOf<T>())
                result.push_back(c->cast<T>());
        }
        return result;
    }

    template<typename T>
    T* capability() {
        const auto c = capabilities<T>();
        if(c.size() > 0) {
            return c.front();
        }
        return nullptr;
    }
};

