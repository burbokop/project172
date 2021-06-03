#include "taskconsole.h"

#include <src/additional.h>
#include <src/context.h>

#include <src/units/unit.h>

#include <src/capabilities/controller.h>

TaskConsole::TaskConsole() {}

void TaskConsole::executeCommand(const std::string &commandLine, e172::ClosableOutputStream &stream, e172::Context* context) {
    bool taskExecuted = false;
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
                            task->connectToOut(stream);
                            task->initFromCommand(args, context);
                            controller->executeRootTask(task, context, [&stream](const auto&){ stream.close(); });
                            taskExecuted = true;
                        } else {
                            stream << "error: " << arg0parts[0] << " unknown task name" << std::endl;
                        }
                    } else {
                        stream << "error: missing controller in unit: " << subjectId << std::endl;
                    }
                } else {
                    stream << "error: unit with id: " + std::to_string(subjectId) + " not found" << std::endl;
                }
            } else {
                stream << "error: " << arg0parts[1] << " invalid id" << std::endl;
            }
        } else {
            stream << "error: first argument must be [taskClass]>[entityId] but entered: " << args[0] << std::endl;
        }
    } else {
        stream << "error: empty args" << std::endl;
    }
    if(!taskExecuted) {
        stream.close();
    }
}

std::list<std::string> TaskConsole::compleateVariants() const {
    return m_taskFactory.typeNames();
}

