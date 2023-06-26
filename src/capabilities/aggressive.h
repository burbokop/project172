#pragma once

#include "controller.h"

namespace proj172::core {

class Aggressive : public Controller {
public:
    Aggressive(e172::FactoryMeta &&meta)
        : Controller(std::move(meta))
    {}

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler);
    void render(e172::Context *context, e172::AbstractRenderer *renderer);

    // Controller interface
public:
    void onHit(e172::Context *context, int health);

private:
    e172::ptr<Unit> chooseTarget(e172::Context *context);

private:
    e172::ptr<Unit> m_target = nullptr;
    bool m_targeted = false;
    bool m_inWarp = false;
    e172::ElapsedTimer m_warpFatigueTimer = e172::ElapsedTimer(10000);
    e172::ElapsedTimer m_chooseTargetTimer = e172::ElapsedTimer((clock() + rand()) % 5000 + 1000);
};

} // namespace proj172::core
