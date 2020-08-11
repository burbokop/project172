#include "entity.h"

#include "objectregistry.h"

namespace e172 {

Entity::Entity() {
    ObjectRegistry::getInstance()->registerObject(this);
}

Entity::~Entity() {
    ObjectRegistry::getInstance()->markAsDeleted(this);
}

}
