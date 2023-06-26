#include "guifocusswitch.h"

#include <src/eventhandler.h>
#include <src/gameapplication.h>

namespace proj172::core {

void GUIFocusSwitch::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
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

void GUIFocusSwitch::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    for(const auto& c : children()) {
        e172::GameApplication::render(c, context, renderer);
    }
}

} // namespace proj172::core
