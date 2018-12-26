#include "engine.h"

Engine::Engine() {
}

Engine::Engine(Loadable *tmp) : Module (tmp) {
}

void Engine::loop(Context *context, Event *event) {
    this->Module::loop(context, event);
}
