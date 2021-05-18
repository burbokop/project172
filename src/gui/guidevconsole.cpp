#include "guidevconsole.h"

#include <src/abstracteventhandler.h>
#include <src/debug.h>

#include <src/graphics/abstractrenderer.h>


GuiDevConsole::GuiDevConsole(const GuiDevConsole::CommandHandlerFunc &commandHandlerFunc) {
    setMargin(32);
    m_commandHandlerFunc = commandHandlerFunc;
}

void GuiDevConsole::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if (eventHandler->keySinglePressed(e172::ScancodeGrave)) {
        consoleEnabled = !consoleEnabled;
        eventHandler->pullText();
    } else if(eventHandler->keySinglePressed(e172::ScancodeReturn)) {
        lines.push_back(cmdPreffix + currentLine);
        if (m_commandHandlerFunc) {
            m_commandHandlerFunc(currentLine, &lines);
        }
        currentLine.clear();
        eventHandler->pullText();
    }
    if (consoleEnabled) {
        currentLine += eventHandler->pullText();
    }
}

void GuiDevConsole::render(e172::AbstractRenderer *renderer) {
    if(consoleEnabled) {
        double offset = 0;
        for(const auto& l : lines) {
            auto size = renderer->drawString(l, e172::Vector(margin() * 2, margin() * 2 + offset), color);
            offset += size.y();
        }

        renderer->drawString(cmdPreffix + currentLine, e172::Vector(margin() * 2, margin() * 2 + offset), color);
        renderer->drawRect(e172::Vector(margin(), margin()), renderer->resolution() - margin(), color);
    }
}
