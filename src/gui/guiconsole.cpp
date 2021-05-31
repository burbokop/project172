#include "guiconsole.h"

#include <src/abstracteventhandler.h>
#include <src/additional.h>
#include <src/context.h>
#include <src/debug.h>

#include <src/graphics/abstractrenderer.h>

#include <src/conversion.h>

void GuiConsole::loadHistory() {
    const auto path = e172::Additional::absolutePath(m_historyPath, std::string());
    history = e172::convert_to<std::vector<std::string>>(e172::Variant::fromJson(e172::Additional::readFile(path)));
}

void GuiConsole::saveHistory() {
    const auto path = e172::Additional::absolutePath(m_historyPath, std::string());
    e172::Additional::writeFile(path, e172::convert_to<e172::Variant>(history).toJson());
}

GuiConsole::GuiConsole(const GuiConsole::CommandHandlerFunc &commandHandlerFunc, const CompletionFunc &completionFunc) {
    setMargin(32);
    m_commandHandlerFunc = commandHandlerFunc;    
    m_completionFunc = completionFunc;

    loadHistory();
    setDepth(1000);
}

GuiConsole::~GuiConsole() {}

void GuiConsole::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if (eventHandler->keySinglePressed(e172::ScancodeGrave)) {
        consoleEnabled = !consoleEnabled;
        eventHandler->pullText();
        if(consoleEnabled) {
            context->setEntityInFocus(this);
        } else {
            context->setEntityInFocus(nullptr);
        }
    }
    if (consoleEnabled) {
        if(eventHandler->keySinglePressed(e172::ScancodeReturn)) {
            lines.push_back(cmdPreffix + currentLine);
            if (m_commandHandlerFunc) {
                m_commandHandlerFunc(currentLine, &lines, context);
            }
            history.push_back(currentLine);
            saveHistory();
            currentLine.clear();
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeBackSpace)) {
            if (!currentLine.empty()) {
                currentLine.pop_back();
            }
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeUp)) {
            if(historyIndex == -1) {
                currentLineBackup = currentLine;
            }
            if (historyIndex < int64_t(history.size())) {
                historyIndex++;
            }
            if (history.size() - historyIndex - 1 < history.size()) {
                currentLine = history[history.size() - historyIndex - 1];
            }
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeDown)) {
            if (historyIndex >= 0) {
                historyIndex--;
            }
            if (history.size() - historyIndex - 1 < history.size()) {
                currentLine = history[history.size() - historyIndex - 1];
            } else if(historyIndex < 0) {
                currentLine = currentLineBackup;
            }
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeTab)) {
            if(m_completionFunc) {
                currentLine = e172::Additional::compleateString(currentLine, m_completionFunc());
            }
        }
        currentLine += eventHandler->pullText();
    }
}

void GuiConsole::render(e172::AbstractRenderer *renderer) {
    if(consoleEnabled) {
        renderer->drawRect(e172::Vector(), renderer->resolution(), 0xaa000000, e172::ShapeFormat(true));

        double offset = 0;
        for(const auto& l : lines) {
            auto size = renderer->drawString(l, e172::Vector(margin() * 2, margin() * 2 + offset), color);
            offset += size.y();
        }

        renderer->drawString(cmdPreffix + currentLine, e172::Vector(margin() * 2, margin() * 2 + offset), color);
        renderer->drawRect(e172::Vector(margin(), margin()), renderer->resolution() - margin(), color);
    }
}
