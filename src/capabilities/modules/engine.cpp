#include "engine.h"

Engine::Engine() {
}

Engine::Engine(Loadable *tmp) : Module (tmp) {
}

bool Engine::forward() {
    animate(Animator::LOOP);
    return true;
}

void Engine::stop() {
    animate(Animator::NOTRENDER);
}

void Engine::tick(Context *context, Event *event) {
    this->Module::tick(context, event);
}

std::string Engine::getInfo() {
    return "EG";
}
