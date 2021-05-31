#include "guicontainer.h"

#include <src/gameapplication.h>

GUIContainer::GUIContainer() {}

void GUIContainer::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    for(const auto& c : children()) {
        e172::GameApplication::proceed(c, context, eventHandler);
    }
}

void GUIContainer::render(e172::AbstractRenderer *renderer) {
    for(const auto& c : children()) {
        e172::GameApplication::render(c, renderer);
    }
}
