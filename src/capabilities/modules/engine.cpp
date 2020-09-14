#include "engine.h"

Engine::Engine() {
}

bool Engine::forward() {
    m_running = true;
    return true;
}

void Engine::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(m_running != m_lastRunning) {
        if(m_running) {
            animate(Animator::Loop);
        } else {
            animate(Animator::NotRender);
        }
    }

    m_lastRunning = m_running;
    m_running = false;

    this->Module::proceed(context, eventHandler);
}

std::string Engine::info() const {
    return "EG";
}
