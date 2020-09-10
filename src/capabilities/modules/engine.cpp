#include "engine.h"

Engine::Engine() {
}

bool Engine::forward() {
    animate(Animator::Loop);
    return true;
}

void Engine::stop() {
    animate(Animator::NotRender);
}

void Engine::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    this->Module::proceed(context, eventHandler);
}

std::string Engine::info() const {
    return "EG";
}
