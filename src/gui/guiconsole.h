#ifndef GUICONSOLE_H
#define GUICONSOLE_H

#include <src/gui/base/guielement.h>
#include <functional>


class GuiConsole : public GUIElement {
    bool consoleEnabled = false;
    std::string currentLine;
    std::list<std::string> lines;
    const uint32_t color = 0x8800ff00;

    const std::string cmdPreffix = "console> ";

    std::string m_historyPath = "~/.project172/console/history";
    std::string m_font = "Consolas";

    std::vector <std::string> history;
    int64_t historyIndex = -1;
    std::string currentLineBackup;
    size_t m_caretteX = 0;
public:
    typedef std::function<void(const std::string &, std::list<std::string> *, e172::Context*)> CommandHandlerFunc;
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
