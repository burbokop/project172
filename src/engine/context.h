#ifndef CONTEXT_H
#define CONTEXT_H

#include <queue>


#include "entity.h"
#include "messagequeue.h"



namespace e172 {

class AssetProvider;
class GameApplication;
class Context : public Object {
    friend GameApplication;
    double m_deltaTime = 0;
    GameApplication *m_application = nullptr;

public:

    enum {
        DELETE_UNIT = 0,
        DELETE_ALL_UNITS,
        SPAWN_EXPLOSIVE,
        SPAWN_ENGINE_EXPLOSIVE,
        SPAWN_ENGINE_PARTICLES,
        SPAWN_UNIT,
        SPAWN_SURFACE,
        ADD_CAPABILITY,
        REMOVE_CAPABILITY,
        EMERGENCY_MESSAGE,
        BACKGROUND_FLASHING,
        FLOATING_MESSAGE,
        CHANGE_RESOLUTION,
        CHANGE_FULLSCREEN,
        CHANGE_ANAGLYPH
    };

private:
    e172::MessageBus<Entity::message_id_t, Variant> m_messageBus;
public:
    Context(GameApplication *application);
    std::string absolutePath(const std::string &path) const;
    std::vector<std::string> arguments() const;
    double deltaTime() const;

    AssetProvider *assetProvider() const;
    std::list<Entity *> entities() const;
    void addEntity(Entity *entity);
    Promice *emitMessage(const Entity::message_id_t &messageId, const Variant &value = Variant());
    bool containsMessage(const Entity::message_id_t &messageId);
    Variant popMessage(const Entity::message_id_t &messageId, bool *ok = nullptr);

    Entity *entityById(const Entity::id_t &id) const;

    void registerMessageHandler(const Entity::message_id_t &messageId, const std::function<void(const Vector&)> &callback);
    template<typename C>
    void registerMessageHandler(const Entity::message_id_t &messageId, C *object, void(C::*callback)(const Vector&)) {
        registerMessageHandler([messageId, object, callback](auto v){
            (object->*callback)(messageId, v);
        });
    }

};

}

#endif // CONTEXT_H
