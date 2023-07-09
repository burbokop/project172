#ifndef __CAPABILITY_H
#define __CAPABILITY_H

#include <e172/entity.h>

class InjectableEntity;

class __Capability : public e172::Entity {
    friend InjectableEntity;
    InjectableEntity *m_parentEntity = nullptr;
public:
    __Capability(e172::FactoryMeta &&meta);

    template<typename T = InjectableEntity>
    InjectableEntity *parentEntity() const {
        return dynamic_cast<T*>(m_parentEntity);
    }
};

#endif // __CAPABILITY_H
