#include "guicontainer.h"

#include <src/gameapplication.h>

namespace proj172::core {

void GUIContainer::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    for(const auto& c : children()) {
        e172::GameApplication::proceed(c, context, eventHandler);
    }
}

void GUIContainer::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    for(const auto& c : children()) {
        e172::GameApplication::render(c, context, renderer);
    }
}

} // namespace proj172::core
