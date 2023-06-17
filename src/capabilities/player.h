#pragma once

#include "controller.h"
#include <queue>
#include <src/abstracteventprovider.h>
#include <src/assettools/loadable.h>

namespace proj172::core {

class Player : public Controller
{
public:
    Player(e172::FactoryMeta &&meta);

    void scheduleDocking(e172::Entity::Id entity);
    bool createDockingSessionWithUnit(e172::Context *context, e172::Entity::Id entity);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    void render(e172::AbstractRenderer *renderer) override;

    // Controller interface
public:
    void onHit(e172::Context *context, int) override;

private:
    bool personalKey(e172::EventHandler *eventHandler, std::string id);

private:
    static const std::map<std::string, e172::Scancode> s_scancode;

    bool m_warpKeyPressed = false;
    std::map<std::string, e172::Scancode> m_personalScancode;
    std::queue<e172::Entity::Id> m_dockRequestedQueue;
};

} // namespace proj172::core
