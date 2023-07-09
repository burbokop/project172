#pragma once

#include "../tasks/task.h"
#include <e172/memcontrol/abstractfactory.h>
#include <e172/utility/closableoutputstream.h>
#include <functional>
#include <list>
#include <map>
#include <string>

namespace proj172::core {

class TaskConsole {
    e172::AbstractFactory<std::string, Task> m_taskFactory;
public:
    TaskConsole();
    void executeCommand(const std::string &commandLine, e172::ClosableOutputStream &stream, e172::Context *context);

    std::list<std::string> compleateVariants() const;

    template<typename T>
    void registerTask() {
        m_taskFactory.registerType<T>();
    }
};

} // namespace proj172::core
