#pragma once

#include <src/gui/base/guielement.h>
#include <src/time/elapsedtimer.h>

namespace proj172::core {

class GUIDebugValueInfo : public GUIElement {
public:
    GUIDebugValueInfo(e172::FactoryMeta &&meta)
        : GUIElement(std::move(meta))
    {}

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::EventHandler *eventHandler) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;

private:
    double m_coef = 6;
    e172::ElapsedTimer m_timer;
};

} // namespace proj172::core
