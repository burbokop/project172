#include "docker.h"

void Docker::attach(Unit *target) {
    UNUSED(target);
}

Docker::Docker() {
}

void Docker::loop(Context *context, Event *event) {
    UNUSED(context);
    UNUSED(event);
}

void Docker::render(Renderer *renderer) {
    UNUSED(renderer);
}
