#pragma once

#include "module.h"

namespace proj172::core {

class Engine : public Module {
public:
    Engine(e172::FactoryMeta &&meta);
    Engine(Loadable *tmp);


    // Entity interface
public:
    bool forward();

    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;

    // IInformative interface
public:
    std::string info() const override;

private:
    bool m_running = false;
    bool m_lastRunning = false;
};

} // namespace proj172::core
