#include "devconsole.h"

#include <src/additional.h>

DevConsole::DevConsole() {}

void DevConsole::addCommand(const std::string &commandName, const DevConsole::CommandHandlerFunc &hf) {
    commands[commandName].push_back(hf);
}

void DevConsole::executeCommand(const std::string &commandLine, std::list<std::string> *lines) {
    auto parts = e172::Additional::split(commandLine, ' ');
    if(!parts.empty()) {
        auto it = commands.find(parts[0]);
        if (it != commands.end()) {
            for(const auto& hf : it->second) {
                hf(parts, lines);
            }
        }
    }
}

void DevConsole::executeCommandToStream(const std::string &commandLine, std::ostream &stream) {
    std::list<std::string> list;
    executeCommand(commandLine, &list);
    for(const auto& l : list) {
        stream << l << "\n";
    }
}

