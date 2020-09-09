#ifndef ENTITY_H
#define ENTITY_H


#include "object.h"
#include "typedefs.h"

namespace e172 {

class AbstractEventHandler;
class AbstractRenderer;
class Context;

class Entity : public Object {
public:
    typedef uintptr_t id_t;
private:
    static inline id_t nextId = 0;
    id_t m_entityId = ++nextId;
    StringSet m_tags;
public:
    Entity();
    void virtual proceed(e172::Context *context, AbstractEventHandler *eventHandler) = 0;
    void virtual render(AbstractRenderer *renderer) = 0;
    virtual ~Entity();
    uint64_t entityId() const;

    StringSet tags() const;

    bool addTag(const String& tag);
    bool removeTag(const String& tag);
    bool containsTag(const String& tag);
};


}

#endif // ENTITY_H
