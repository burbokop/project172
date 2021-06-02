#include "guiconsole.h"

#include <src/abstracteventhandler.h>
#include <src/additional.h>
#include <src/context.h>
#include <src/debug.h>

#include <src/graphics/abstractrenderer.h>

#include <src/conversion.h>


void GuiConsole::loadHistory() {
    const auto path = e172::Additional::absolutePath(m_historyPath, std::string());
    m_history = e172::convert_to<std::vector<std::string>>(e172::Variant::fromJson(e172::Additional::readFile(path)));
}

void GuiConsole::saveHistory() {
    const auto path = e172::Additional::absolutePath(m_historyPath, std::string());
    e172::Additional::writeFile(path, e172::convert_to<e172::Variant>(m_history).toJson());
}

GuiConsole::GuiConsole(const GuiConsole::CommandHandlerFunc &commandHandlerFunc, const CompletionFunc &completionFunc) {
    setMargin(32);
    m_commandHandlerFunc = commandHandlerFunc;
    m_completionFunc = completionFunc;

    loadHistory();
    setDepth(1000);

    m_streamPool = e172::CallbackOutputStream::SingleElementPool([this](const std::string& str){
        m_text += str;
    });
}

GuiConsole::~GuiConsole() {}

void GuiConsole::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if (eventHandler->keySinglePressed(e172::ScancodeGrave)) {
        m_consoleEnabled = !m_consoleEnabled;
        eventHandler->pullText();
        if(m_consoleEnabled) {
            context->setEntityInFocus(this);
        } else {
            context->setEntityInFocus(nullptr);
        }
    }
    if (m_consoleEnabled) {
        if(m_streamPool.available() && eventHandler->keySinglePressed(e172::ScancodeReturn)) {
            m_text += m_cmdPreffix + m_currentLine + "\n";
            if (m_commandHandlerFunc) {
                m_commandHandlerFunc(m_currentLine, *m_streamPool.use(), context);
            }
            m_history.push_back(m_currentLine);
            saveHistory();
            m_currentLine.clear();
            m_caretteX = 0;
            eventHandler->pullText();
        } else if(m_streamPool.available() && eventHandler->keySinglePressed(e172::ScancodeBackSpace)) {
            if (!m_currentLine.empty() && m_caretteX > 0 && m_caretteX <= m_currentLine.size()) {
                m_currentLine.erase(--m_caretteX, 1);
            }
            eventHandler->pullText();
        } else if(m_streamPool.available() && eventHandler->keySinglePressed(e172::ScancodeUp)) {
            if(m_historyIndex == -1) {
                m_currentLineBackup = m_currentLine;
            }
            if (m_historyIndex < int64_t(m_history.size())) {
                m_historyIndex++;
            }
            if (m_history.size() - m_historyIndex - 1 < m_history.size()) {
                m_currentLine = m_history[m_history.size() - m_historyIndex - 1];
                m_caretteX = m_currentLine.size();
            }
            eventHandler->pullText();
        } else if(m_streamPool.available() && eventHandler->keySinglePressed(e172::ScancodeDown)) {
            if (m_historyIndex >= 0) {
                m_historyIndex--;
            }
            if (m_history.size() - m_historyIndex - 1 < m_history.size()) {
                m_currentLine = m_history[m_history.size() - m_historyIndex - 1];
                m_caretteX = m_currentLine.size();
            } else if(m_historyIndex < 0) {
                m_currentLine = m_currentLineBackup;
                m_caretteX = m_currentLine.size();
            }
            eventHandler->pullText();
        } else if(m_streamPool.available() && eventHandler->keySinglePressed(e172::ScancodeTab)) {
            if(m_completionFunc) {
                m_currentLine = e172::Additional::compleateString(m_currentLine, m_completionFunc());
                m_caretteX = m_currentLine.size();
            }
            eventHandler->pullText();
        } else if(m_streamPool.available() && eventHandler->keySinglePressed(e172::ScancodeLeft)) {
            if(m_caretteX > 0) {
                m_caretteX--;
            }
            eventHandler->pullText();
        } else if(m_streamPool.available() && eventHandler->keySinglePressed(e172::ScancodeRight)) {
            if(m_caretteX < m_currentLine.size()) {
                m_caretteX++;
            }
            eventHandler->pullText();
        }
        if(m_streamPool.available()) {
            if(m_caretteX >= 0 && m_caretteX <= m_currentLine.size()) {
                const auto pendingText = eventHandler->pullText();
                m_currentLine.insert(m_caretteX, pendingText);
                m_caretteX += pendingText.size();
            }
        } else {
            eventHandler->pullText();
        }
    }
}

void GuiConsole::render(e172::AbstractRenderer *renderer) {
    if(m_consoleEnabled) {
        renderer->drawRect(e172::Vector(), renderer->resolution(), 0xaa000000, e172::ShapeFormat(true));
        const auto textFormat = e172::TextFormat::fromFont(m_font, 20);

        const auto offset = renderer->drawText(m_text, e172::Vector(margin() * 2, margin() * 2), renderer->resolution().x() - margin() * 4, m_color, textFormat);

        const auto lineStart = e172::Vector(margin() * 2, margin() * 2 + offset.y());
        renderer->drawRect(e172::Vector(margin(), margin()), renderer->resolution() - margin(), m_color);
        if(m_streamPool.available()) {
            renderer->drawString(m_cmdPreffix + m_currentLine, lineStart, m_color, textFormat);
            renderer->drawLine(
                        lineStart + e172::Vector((m_cmdPreffix.size() + m_caretteX) * textFormat.fontWidth(), 0),
                        lineStart + e172::Vector((m_cmdPreffix.size() + m_caretteX) * textFormat.fontWidth(), textFormat.fontHeight()),
                        m_color
                        );
        }
    }
}
