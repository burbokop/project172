#ifndef ENGINE_H
#define ENGINE_H

#include "module.h"

class Engine : public Module {
    bool m_running = false;
    bool m_lastRunning = false;
public:
    Engine();
    Engine(Loadable *tmp);


    // Entity interface
public:
    bool forward();

    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;

    // IInformative interface
public:
    std::string info() const override;
};

#endif // ENGINE_H
