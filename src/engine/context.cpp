#include "additional.h"
#include "context.h"


#include "objectregistry.h"
#include "gameapplication.h"

namespace e172 {


double Context::deltaTime() const {
    return m_deltaTime;
}

Variant Context::property(const std::string &propertyId) const {
    const auto it = m_properties.find(propertyId);
    if(it != m_properties.end())
        return it->second;

    return e172::Variant();
}

void Context::setProperty(const std::string &propertyId, const Variant &value) {
    m_properties[propertyId] = value;
}

AssetProvider *Context::assetProvider() const {
    if(m_application)
        return m_application->assetProvider();
    return nullptr;
}

std::list<Entity*> Context::entities() const {
    if(m_application)
        return m_application->entities();
    return std::list<Entity*>();
}

void Context::addEntity(Entity *entity) {
    m_application->addEntity(entity);
}

Context::Context(GameApplication *application) {
    m_application = application;
    m_messageQueue.setExceptionHandlingMode(decltype (m_messageQueue)::WarningException);
    m_messageQueue.setMessageLifeTime(1);
}

std::string Context::absolutePath(const std::string &path) const {
    if(m_application) {
        const auto args = m_application->arguments();
        if(args.size() > 0) {
            return e172::Additional::absolutePath(path, args[0]);
        }
    }
    return std::string();
}

std::vector<std::string> Context::arguments() const {
    if(m_application)
        return m_application->arguments();
    return std::vector<std::string>();
}

Promice *Context::emitMessage(const MessageId &messageId, const Variant &value) {
    return m_messageQueue.emitMessage(messageId, value);
}

Entity *Context::entityById(const Entity::id_t &id) const {
    const auto e = m_application->entities();
    for(auto a : e) {
        if(a && a->entityId() == id)
            return a;
    }
    return nullptr;
}

Entity *Context::autoIteratingEntity() const {
    if(m_application) {
        return m_application->autoIteratingEntity();
    }
    return nullptr;
}


}
