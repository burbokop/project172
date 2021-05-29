#include "taskconsole.h"

#include <src/additional.h>
#include <src/context.h>

#include <src/units/unit.h>

#include <src/capabilities/controller.h>

TaskConsole::TaskConsole() {}

void TaskConsole::executeCommand(const std::string &commandLine, std::list<std::string> *lines, e172::Context* context) {
    auto args = e172::Additional::split(commandLine, ' ');
    if(!args.empty()) {
        const auto arg0parts = e172::Additional::split(args[0], '>');
        if(arg0parts.size() == 2) {
            bool ok = false;
            auto subjectId = e172::Variant(arg0parts[1]).toNumber<e172::Entity::id_t>(&ok);
            if(ok) {
                if(const auto& subject = context->entityById<Unit>(subjectId)) {
                    if(auto controller = subject->capability<Controller>()) {
                        if(auto task = m_taskFactory.create(arg0parts[0])) {
                            task->initFromCommand(args, lines, context);
                            controller->executeRootTask(task, context);
                        } else {
                            lines->push_back("error: " + arg0parts[0] + " unknown task name");
                        }
                    } else {
                        lines->push_back("error: missing controller in unit: " + std::to_string(subjectId));
                    }
                } else {
                    lines->push_back("error: unit with id: " + std::to_string(subjectId) + " not found");
                }
            } else {
                lines->push_back("error: " + arg0parts[1] + " invalid id");
            }
        } else {
            lines->push_back("error: first argument must be [taskClass]>[entityId] but entered: " + args[0]);
        }
    } else {
        lines->push_back("error: empty args");
    }
}

void TaskConsole::executeCommandToStream(const std::string &commandLine, std::ostream &stream, e172::Context* context) {
    std::list<std::string> list;
    executeCommand(commandLine, &list, context);
    for(const auto& l : list) {
        stream << l << "\n";
    }
}

