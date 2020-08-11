#ifndef SDLEVENTHANDLER_H
#define SDLEVENTHANDLER_H

#include "engine/abstracteventhandler.h"

union SDL_Event;

class SDLEventHandler : public e172::AbstractEventHandler {
    void handleEvent(SDL_Event event);
    static constexpr size_t bufferSize = 512;
    bool m_holdedKeys[bufferSize];
    bool m_singlePressedKeys[bufferSize];
    e172::Vector m_mousePosition;
    bool m_exitFlag = false;
public:
    SDLEventHandler();

    // AbstractEventHandler interface
public:
    virtual bool exitFlag() const override;
    virtual bool keyHolded(e172::Scancode key) const override;
    virtual bool keySinglePressed(e172::Scancode key) const override;
    virtual void update() override;
    virtual e172::Vector mousePosition() const override;
};

#endif // SDLEVENTHANDLER_H
