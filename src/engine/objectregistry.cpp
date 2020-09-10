#include "objectregistry.h"


std::map<e172::Object*, bool> e172::ObjectRegistry::objects;


void e172::ObjectRegistry::registerObject(Object *object) {
    objects[object] = true;
}

void e172::ObjectRegistry::markAsDeleted(Object *object) {
    objects[object] = false;
}

bool e172::ObjectRegistry::exists(Object *object) {
    if(object == nullptr) return false;
    return objects[object];
}

bool e172::ObjectRegistry::isDeleted(Object *object) {
    if(object == nullptr) return true;
    return !objects[object];
}

unsigned long e172::ObjectRegistry::size() {
    return objects.size();
}

