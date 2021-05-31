#ifndef TASKCONSOLE_H
#define TASKCONSOLE_H

#include <list>
#include <string>
#include <functional>
#include <map>

#include <src/memcontrol/abstractfactory.h>

#include <src/tasks/task.h>


class TaskConsole {
    e172::AbstractFactory<std::string, Task> m_taskFactory;
public:
    TaskConsole();
    void executeCommand(const std::string &commandLine, std::list<std::string> *lines, e172::Context *context);

    std::list<std::string> compleateVariants() const;

    template<typename T>
    void registerTask() {
        m_taskFactory.registerType<T>();
    }

    void executeCommandToStream(const std::string &commandLine, std::ostream& stream, e172::Context* context);
};

#endif // TASKCONSOLE_H
