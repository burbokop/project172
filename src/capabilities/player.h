#ifndef PLAYER_H
#define PLAYER_H


#include "controller.h"

#include <src/engine/abstracteventhandler.h>
#include <queue>
#include <src/engine/assettools/loadable.h>


class Player : public Controller {
private:
    static const std::map<std::string, e172::Scancode> scancode;

    bool warpKeyPressed = false;
    std::map<std::string, e172::Scancode> personalScancode;
    bool personalKey(e172::AbstractEventHandler *eventHandler, std::string id);

    std::queue<e172::Entity::id_t> dockRequestedQueue;
public:
    Player();
    Player(Loadable* tmp);
    void setArmor(Ship *armor);

    void dock(e172::Entity::id_t entity);
    bool dockImmediately(e172::Context *context, e172::Entity::id_t entity);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    void render(e172::AbstractRenderer *renderer) override;

    // Controller interface
public:
    void onHit(e172::Context* context, int) override;
};

#endif // PLAYER_H
