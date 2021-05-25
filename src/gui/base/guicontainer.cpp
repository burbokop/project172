#include "guicontainer.h"

GUIContainer::GUIContainer() {}

void GUIContainer::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    for(const auto& c : children()) {
        c->proceed(context, eventHandler);
    }
}

void GUIContainer::render(e172::AbstractRenderer *renderer) {
    for(const auto& c : children()) {
        c->render(renderer);
    }
}
