#include "engine.h"

namespace proj172::core {

Engine::Engine(e172::FactoryMeta &&meta)
    : Module(std::move(meta))
{}

bool Engine::forward() {
    m_running = true;
    return true;
}

void Engine::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    if(m_running != m_lastRunning) {
        if(m_running) {
            animate(e172::Animator::Loop);
        } else {
            animate(e172::Animator::NotRender);
        }
    }

    m_lastRunning = m_running;
    m_running = false;

    this->Module::proceed(context, eventHandler);
}

std::string Engine::info() const {
    return m_running ? "EG running" : "EG stoped";
}

} // namespace proj172::core
