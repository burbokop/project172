#ifndef GUICONSOLE_H
#define GUICONSOLE_H

#include <src/gui/base/guielement.h>
#include <functional>
#include <src/utility/closableoutputstream.h>

class GuiConsole : public GUIElement {
    bool m_consoleEnabled = false;
    std::string m_currentLine;
    std::string m_text;
    const uint32_t m_color = 0x8800ff00;

    const std::string m_cmdPreffix = "console> ";

    std::string m_historyPath = "~/.project172/console/history";
    std::string m_font = "Consolas";

    std::vector <std::string> m_history;
    int64_t m_historyIndex = -1;
    std::string m_currentLineBackup;
    size_t m_caretteX = 0;

    e172::ClosableOutputStream *m_currentStream = nullptr;
    bool m_needDestroyStream = false;
public:
    typedef std::function<void(const std::string &, e172::ClosableOutputStream&, e172::Context*)> CommandHandlerFunc;
    typedef std::function<std::list<std::string>()> CompletionFunc;
private:
    CommandHandlerFunc m_commandHandlerFunc;
    CompletionFunc m_completionFunc;

    void loadHistory();
    void saveHistory();
public:
    GuiConsole(const CommandHandlerFunc& commandHandlerFunc, const CompletionFunc& completionFunc = nullptr);
    virtual ~GuiConsole();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GUICONSOLE_H
