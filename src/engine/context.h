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
    typedef Variant MessageId;

    enum {
        DELETE_UNIT = 0,
        DELETE_ALL_UNITS,
        SPAWN_EXPLOSIVE,
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
    e172::MessageQueue<MessageId, Variant> m_messageQueue;
public:
    Context(GameApplication *application);
    std::string absolutePath(const std::string &path) const;
    std::vector<std::string> arguments() const;
    double deltaTime() const;

    AssetProvider *assetProvider() const;
    std::list<Entity *> entities() const;
    void addEntity(Entity *entity);
    Promice *emitMessage(const MessageId &messageId, const Variant &value = Variant());
    bool containsMessage(const MessageId &messageId);


    Variant popMessage(const MessageId &messageId, bool *ok = nullptr);
    inline void popMessage(const MessageId &messageId, const std::function<void(Context *, const Variant&)>& callback) {
        m_messageQueue.popMessage(messageId, [this, callback](const auto& value) { callback(this, value); });
    }
    template<typename C>
    void popMessage(const MessageId &messageId, C *object, void(C::*callback)(Context *, const Variant&)) {
        m_messageQueue.popMessage(messageId, [object, this, callback](const auto& value) { (object->*callback)(this, value); });
    }



    Entity *entityById(const Entity::id_t &id) const;

    template<typename T>
    T *entityById(const Entity::id_t &id) const {
        return dynamic_cast<T*>(entityById(id));
    }

    void registerMessageHandler(const MessageId &messageId, const std::function<void(const Vector&)> &callback);
    template<typename C>
    void registerMessageHandler(const MessageId &messageId, C *object, void(C::*callback)(const Vector&)) {
        registerMessageHandler([messageId, object, callback](auto v){
            (object->*callback)(messageId, v);
        });
    }

};

}

#endif // CONTEXT_H
