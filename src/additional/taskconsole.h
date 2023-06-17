#pragma once

#include <list>
#include <string>
#include <functional>
#include <map>
#include <src/memcontrol/abstractfactory.h>
#include <src/tasks/task.h>
#include <src/utility/closableoutputstream.h>

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
