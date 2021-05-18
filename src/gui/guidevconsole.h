#ifndef GUIDEVCONSOLE_H
#define GUIDEVCONSOLE_H

#include <src/gui/base/guielement.h>



class GuiDevConsole : public GUIElement {
    bool consoleEnabled = false;
    std::string currentLine;
    std::list<std::string> lines;
    const uint32_t color = 0x8800ff00;

    const std::string cmdPreffix = ": ";

public:
    typedef std::function<void(const std::string &, std::list<std::string> *)> CommandHandlerFunc;
private:
    CommandHandlerFunc m_commandHandlerFunc;
public:
    GuiDevConsole(const CommandHandlerFunc& commandHandlerFunc);


    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GUIDEVCONSOLE_H
