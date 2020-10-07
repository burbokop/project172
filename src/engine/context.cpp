#include "additional.h"
#include "context.h"


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

Observer<Variant> Context::settingValue(const std::string &id) const {
    auto it = m_settings.find(id);
    if(it == m_settings.end())
        it = const_cast<Context*>(this)->m_settings.insert(it, { id, Variant::fromString(Additional::readVof(absolutePath(SettingsFilePath), id)) });

    return it->second;
}

void Context::setSettingValue(const std::string &id, const Variant &value) {
    const auto it = m_settings.find(id);
    if(it == m_settings.end()) {
        Additional::writeVof(SettingsFilePath, id, value.toString());
        m_settings.insert(it, { id, value });
    } else {
        if(it->second != value) {
            Additional::writeVof(SettingsFilePath, id, value.toString());
            it->second = value;
        }
    }
}

AssetProvider *Context::assetProvider() const {
    if(m_application)
        return m_application->assetProvider();
    return nullptr;
}

std::list<ptr<Entity>> Context::entities() const {
    if(m_application)
        return m_application->entities();
    return std::list<ptr<Entity>>();
}

void Context::addEntity(const ptr<Entity> &entity) {
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

std::shared_ptr<Promice> Context::emitMessage(const MessageId &messageId, const Variant &value) {
    return m_messageQueue.emitMessage(messageId, value);
}

ptr<Entity> Context::entityById(const Entity::id_t &id) const {
    const auto e = m_application->entities();
    for(auto a : e) {
        if(a && a->entityId() == id)
            return a;
    }
    return nullptr;
}

ptr<Entity> Context::autoIteratingEntity() const {
    if(m_application) {
        return m_application->autoIteratingEntity();
    }
    return nullptr;
}

ElapsedTimer::time_t Context::proceedDelay() const {
    if(m_application) {
        return m_application->proceedDelay();
    }
    return 0;
}

ElapsedTimer::time_t Context::renderDelay() const {
    if(m_application) {
        return m_application->renderDelay();
    }
    return 0;
}


}
