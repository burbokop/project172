#ifndef OBJECTREGISTER_H
#define OBJECTREGISTER_H

#include <map>


#include "object.h"


class ObjectRegistry {
private:
    static ObjectRegistry *instance;
    std::map<Object*, bool> *objects;
    ObjectRegistry();
public:
    static ObjectRegistry *getInstance();
    void registerObject(Object* object);
    void markAsDeleted(Object* object);

    bool exists(Object* object);
    bool isDeleted(Object *object);
    unsigned long getSize();
};

#define EXISTS(OBJECT) if(ObjectRegistry::getInstance()->exists(OBJECT))
#define PROTECT_OBJECT(OBJECT) if(ObjectRegistry::getInstance()->isDeleted(OBJECT)) { Debug::err(Debug::Code::APPEAL_TO_REMOVED, __PRETTY_FUNCTION__); return; }


#endif // OBJECTREGISTER_H
