#include "entity.h"

#include "context.h"
#include "objectregistry.h"

namespace e172 {

uint64_t Entity::entityId() const {
    return m_entityId;
}

Entity::Entity() {
    ObjectRegistry::registerObject(this);
}

Entity::~Entity() {
    ObjectRegistry::markAsDeleted(this);
}


}
