#ifndef ENTITY_H
#define ENTITY_H




#include "object.h"

namespace e172 {

class AbstractEventHandler;
class AbstractRenderer;
class Context;

class Entity : public Object {
public:
    Entity();
    void virtual proceed(e172::Context *context, AbstractEventHandler *eventHandler) = 0;
    void virtual render(AbstractRenderer *renderer) = 0;
    virtual ~Entity();
};


}

#endif // ENTITY_H
