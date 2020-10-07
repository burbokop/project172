#include "entity.h"

#include "context.h"

namespace e172 {

uint64_t Entity::entityId() const {
    return m_entityId;
}

StringSet Entity::tags() const {
    return m_tags;
}

bool Entity::addTag(const String &tag) {
    return m_tags.insert(tag).second;
}

bool Entity::removeTag(const String &tag) {
    const auto it = m_tags.find(tag);
    if(it != m_tags.end()) {
        m_tags.erase(it);
        return true;
    }
    return false;
}

bool Entity::containsTag(const String &tag) {
    return m_tags.find(tag) != m_tags.end();
}

Entity::Entity() {}

Entity::~Entity() {}


}
