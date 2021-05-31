#include "guifocusswitch.h"

#include <src/gameapplication.h>

GUIFocusSwitch::GUIFocusSwitch(e172::Scancode keyLast, e172::Scancode keyNext) {
    m_keyLast = keyLast;
    m_keyNext = keyNext;
}

void GUIFocusSwitch::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    const auto ch = children();
    if(eventHandler->keySinglePressed(m_keyLast)) {
        if(m_currentIndex != 0)
            m_currentIndex--;
    } else if(eventHandler->keySinglePressed(m_keyNext)) {
        if(m_currentIndex + 1 < ch.size())
            m_currentIndex++;
    }

    size_t i = 0;
    for(const auto& c : ch) {
        if(m_currentIndex == i) {
            c->setInFocus(true);
        } else {
            c->setInFocus(false);
        }
        e172::GameApplication::proceed(c, context, eventHandler);
        ++i;
    }
}

void GUIFocusSwitch::render(e172::AbstractRenderer *renderer) {
    for(const auto& c : children()) {
        e172::GameApplication::render(c, renderer);
    }
}
