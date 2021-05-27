#ifndef TASK_H
#define TASK_H

#include <src/object.h>

#include <src/utility/ptr.h>

#include <list>
#include <set>

class Controller;
namespace e172 {
class Context;
}

class Task : public e172::Object {
    friend Controller;
    bool m_running = false;

    e172::ptr<Task> m_parentTask;
    e172::ptr<Controller> m_parentController;
    std::set<e172::ptr<Task>> m_children;
    std::list<e172::ptr<Task>> m_trash;
    std::list<std::function<void()>> m_onCompleatedSignal;
public:
    void completeTask();

    Task();
    bool running() const;
    e172::ptr<Task> parentTask() const;

    bool executeChildTask(const e172::ptr<Task>& task, e172::Context *context, const std::function<void()>&onCompleated = nullptr);

    void proceedBranch(e172::Context *context);
    virtual void proceed(e172::Context *context) = 0;
    virtual bool start(e172::Context *context) = 0;

    virtual ~Task();
    e172::ptr<Controller> parentController() const;
};

#endif // TASK_H
