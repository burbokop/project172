#ifndef ENTITY_H
#define ENTITY_H




#include "object.h"
#include "variant.h"

#include <inttypes.h>

namespace e172 {

class AbstractEventHandler;
class AbstractRenderer;
class Context;

class Entity : public Object {
public:
    typedef uintptr_t id_t;
    typedef Variant message_id_t;
private:
    static inline id_t nextId = 0;
    id_t m_entityId = ++nextId;
public:
    Entity();
    void virtual proceed(e172::Context *context, AbstractEventHandler *eventHandler) = 0;
    void virtual render(AbstractRenderer *renderer) = 0;
    virtual ~Entity();
    uint64_t entityId() const;
};


}

#endif // ENTITY_H
