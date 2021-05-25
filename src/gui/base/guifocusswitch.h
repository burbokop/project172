#ifndef GUIFOCUSSWITCH_H
#define GUIFOCUSSWITCH_H

#include "guielement.h"

#include <src/abstracteventhandler.h>

class GUIFocusSwitch : public GUIElement {
    size_t m_currentIndex = 0;
    e172::Scancode m_keyLast;
    e172::Scancode m_keyNext;
public:
    GUIFocusSwitch(e172::Scancode keyLast, e172::Scancode keyNext);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GUIFOCUSSWITCH_H
