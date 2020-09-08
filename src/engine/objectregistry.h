#ifndef OBJECTREGISTER_H
#define OBJECTREGISTER_H

#include <map>


#include "object.h"

namespace e172 {


class ObjectRegistry {
    static std::map<Object*, bool> objects;
public:
    static void registerObject(Object* object);
    static void markAsDeleted(Object* object);

    static bool exists(Object* object);
    static bool isDeleted(Object *object);
    static unsigned long size();
};

struct alive_t {};

static const inline alive_t Alive;

bool operator ==(Object *object, const alive_t&);
bool operator ==(const alive_t&, Object *object);
bool operator !=(Object *object, const alive_t&);
bool operator !=(const alive_t&, Object *object);

}




#endif // OBJECTREGISTER_H
