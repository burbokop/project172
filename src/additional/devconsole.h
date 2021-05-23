#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include <list>
#include <string>
#include <functional>
#include <map>


class DevConsole {
public:
    typedef std::function<void(const std::vector<std::string>&, std::list<std::string> *)> CommandHandlerFunc;
private:
    std::map<std::string, std::list<CommandHandlerFunc>> commands;
public:
    DevConsole();
    void addCommand(const std::string &commandName, const CommandHandlerFunc& hf);
    void executeCommand(const std::string &commandLine, std::list<std::string> *lines);

    void executeCommandToStream(const std::string &commandLine, std::ostream& stream);
};

#endif // DEVCONSOLE_H
