#pragma once

#include "guielement.h"
#include <src/abstracteventprovider.h>

namespace proj172::core {

class GUIFocusSwitch : public GUIElement {
public:
    GUIFocusSwitch(e172::FactoryMeta &&meta, e172::Scancode keyLast, e172::Scancode keyNext)
        : GUIElement(std::move(meta))
        , m_keyLast(keyLast)
        , m_keyNext(keyNext)
    {}

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    void render(e172::AbstractRenderer *renderer) override;

private:
    size_t m_currentIndex = 0;
    e172::Scancode m_keyLast;
    e172::Scancode m_keyNext;
};

} // namespace proj172::core
