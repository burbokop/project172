#pragma once

#include "guielement.h"

namespace proj172::core {

class GUIContainer : public GUIElement {
public:
    GUIContainer(e172::FactoryMeta &&meta)
        : GUIElement(std::move(meta))
    {}

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
};

} // namespace proj172::core
