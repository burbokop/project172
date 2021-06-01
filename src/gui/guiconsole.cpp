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
            m_caretteX = 0;
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeBackSpace)) {
            if (!currentLine.empty() && m_caretteX > 0 && m_caretteX <= currentLine.size()) {
                currentLine.erase(--m_caretteX, 1);
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
                m_caretteX = currentLine.size();
            }
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeDown)) {
            if (historyIndex >= 0) {
                historyIndex--;
            }
            if (history.size() - historyIndex - 1 < history.size()) {
                currentLine = history[history.size() - historyIndex - 1];
                m_caretteX = currentLine.size();
            } else if(historyIndex < 0) {
                currentLine = currentLineBackup;
                m_caretteX = currentLine.size();
            }
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeTab)) {
            if(m_completionFunc) {
                currentLine = e172::Additional::compleateString(currentLine, m_completionFunc());
                m_caretteX = currentLine.size();
            }
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeLeft)) {
            if(m_caretteX > 0) {
                m_caretteX--;
            }
            eventHandler->pullText();
        } else if(eventHandler->keySinglePressed(e172::ScancodeRight)) {
            if(m_caretteX < currentLine.size()) {
                m_caretteX++;
            }
            eventHandler->pullText();
        }
        if(m_caretteX >= 0 && m_caretteX <= currentLine.size()) {
            const auto pendingText = eventHandler->pullText();
            currentLine.insert(m_caretteX, pendingText);
            m_caretteX += pendingText.size();
        }
    }
}

void GuiConsole::render(e172::AbstractRenderer *renderer) {
    if(consoleEnabled) {
        renderer->drawRect(e172::Vector(), renderer->resolution(), 0xaa000000, e172::ShapeFormat(true));
        const auto textFormat = e172::TextFormat::fromFont(m_font, 20);

        double offset = 0;
        for(const auto& l : lines) {
            auto size = renderer->drawString(l, e172::Vector(margin() * 2, margin() * 2 + offset), color, textFormat);
            offset += size.y();
        }


        const auto lineStart = e172::Vector(margin() * 2, margin() * 2 + offset);
        renderer->drawString(cmdPreffix + currentLine, lineStart, color, textFormat);
        renderer->drawRect(e172::Vector(margin(), margin()), renderer->resolution() - margin(), color);

        renderer->drawLine(
                    lineStart + e172::Vector((cmdPreffix.size() + m_caretteX) * textFormat.fontWidth(), 0),
                    lineStart + e172::Vector((cmdPreffix.size() + m_caretteX) * textFormat.fontWidth(), textFormat.fontHeight()),
                    color
                    );
    }
}
