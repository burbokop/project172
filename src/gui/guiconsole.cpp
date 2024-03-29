#include "guiconsole.h"

#include <e172/abstracteventprovider.h>
#include <e172/additional.h>
#include <e172/context.h>
#include <e172/conversion.h>
#include <e172/debug.h>
#include <e172/eventhandler.h>
#include <e172/graphics/abstractrenderer.h>

namespace proj172::core {

void GuiConsole::loadHistory() {
    const auto path = e172::Additional::absolutePath(m_historyPath, std::string());
    m_history = e172::convert_to<std::vector<std::string>>(e172::Variant::fromJson(e172::Additional::readFile(path)));
}

void GuiConsole::saveHistory() {
    const auto path = e172::Additional::absolutePath(m_historyPath, std::string());
    e172::Additional::writeFile(path, e172::convert_to<e172::Variant>(m_history).toJson());
}

GuiConsole::GuiConsole(e172::FactoryMeta &&meta,
                       const GuiConsole::CommandHandlerFunc &commandHandlerFunc,
                       const CompletionFunc &completionFunc)
    : GUIElement(std::move(meta))
{
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

void GuiConsole::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
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

void GuiConsole::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    if(m_consoleEnabled) {
        renderer->drawRect({},
                           renderer->resolution().into<double>(),
                           0xaa000000,
                           e172::ShapeFormat(true));
        const auto textFormat = e172::TextFormat::fromFont(m_font, 20);

        const auto offset = renderer->drawText(m_text,
                                               e172::Vector<double>(margin() * 2, margin() * 2),
                                               renderer->resolution().x() - margin() * 4,
                                               m_color,
                                               textFormat);

        const auto lineStart = e172::Vector<double>(margin() * 2, margin() * 2 + offset.y());
        renderer->drawRect(e172::Vector<double>(margin(), margin()),
                           renderer->resolution().into<double>() - margin(),
                           m_color);
        if(m_streamPool.available()) {
            renderer->drawString(m_cmdPreffix + m_currentLine, lineStart, m_color, textFormat);
            if(m_caretteDisplayTimer.check()) {
                m_displayCarette = !m_displayCarette;
            }
            if(m_displayCarette) {
                renderer->drawLine(lineStart
                                       + e172::Vector<double>((m_cmdPreffix.size() + m_caretteX)
                                                                  * textFormat.fontWidth(),
                                                              0),
                                   lineStart
                                       + e172::Vector<double>((m_cmdPreffix.size() + m_caretteX)
                                                                  * textFormat.fontWidth(),
                                                              textFormat.fontHeight()),
                                   m_color);
            }
        }
    }
}

} // namespace proj172::core
