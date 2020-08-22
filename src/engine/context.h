#ifndef CONTEXT_H
#define CONTEXT_H

#include <queue>

#include <additional/e_variant.h>



#include "gui/guimain.h"
#include "near.h"
#include "background.h"
#include "entity.h"



namespace e172 {

class AssetProvider;
class GameApplication;
class Context : public Object {
    friend GameApplication;
    double m_deltaTime = 0;
    GameApplication *m_appliation = nullptr;

    struct Request {
        Entity *requester;
        unsigned command;
        old::Variant argument;
    };
public:
    static const unsigned DELETE_UNIT;
    static const unsigned SPAWN_EXPLOSIVE;
    static const unsigned SPAWN_ENGINE_EXPLOSIVE;
    static const unsigned SPAWN_ENGINE_PARTICLES;
    static const unsigned SPAWN_UNIT;
    static const unsigned SPAWN_SURFACE;
    static const unsigned ADD_CAPABILITY;
    static const unsigned REMOVE_CAPABILITY;

    static const unsigned EMERGENCY_MESSAGE;
    static const unsigned BACKGROUND_FLASHING;
    static const unsigned FLOATING_MESSAGE;

private:
    std::queue<Request> eventQueue;
    std::list<Entity*> *m_entities;

    AssetProvider *m_assetProvider= nullptr;

    void handleRequest(Request request);
public:
    Context(std::list<Entity*> *entities = nullptr, AssetProvider *assetProvider = nullptr);
    std::string absolutePath(const std::string &path) const;
    std::vector<std::string> arguments() const;

    [[deprecated]]
    std::list<Entity*> *entities() const;
    AssetProvider *assetProvider() const;

    void addEvent(Entity *requester, unsigned command, old::Variant argument = old::Variant());

    void handleEvents();

    double deltaTime() const;

    [[deprecated]]
    GameApplication *appliation() const;
};

}

#endif // CONTEXT_H
