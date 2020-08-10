#include "engine.h"

Engine::Engine() {
}

bool Engine::forward() {
    animate(Animator::LOOP);
    return true;
}

void Engine::stop() {
    animate(Animator::NOTRENDER);
}

void Engine::tick(Context *context, e172::AbstractEventHandler *eventHandler) {
    this->Module::tick(context, eventHandler);
}

std::string Engine::getInfo() {
    return "EG";
}
