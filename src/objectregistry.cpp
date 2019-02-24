#include "objectregistry.h"


ObjectRegistry *ObjectRegistry::instance = nullptr;

ObjectRegistry::ObjectRegistry() {
    objects = new std::map<Object*, bool>();
}

ObjectRegistry *ObjectRegistry::getInstance() {
    if(instance == nullptr) instance = new ObjectRegistry();
    return instance;
}

void ObjectRegistry::registerObject(Object *object) {
    objects->operator[](object) = true;
}

void ObjectRegistry::markAsDeleted(Object *object) {
    objects->operator[](object) = false;
}

bool ObjectRegistry::exists(Object *object) {
    if(object == nullptr) return false;
    return objects->operator[](object);
}

bool ObjectRegistry::isDeleted(Object *object) {
    if(object == nullptr) return true;
    return !objects->operator[](object);
}

unsigned long ObjectRegistry::getSize() {
    return objects->size();
}
