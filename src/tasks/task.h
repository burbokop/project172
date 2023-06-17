#pragma once

#include <src/object.h>
#include <src/variant.h>
#include <src/utility/closableoutputstream.h>
#include <src/utility/ptr.h>
#include <src/utility/signalstreambuffer.h>
#include <list>
#include <set>

namespace e172 {
class Context;
}

namespace proj172::core {

class Controller;

class Task : public e172::Object {
    friend Controller;
    bool m_running = false;

    e172::ptr<Task> m_parentTask;
    e172::ptr<Controller> m_parentController;
    std::set<e172::ptr<Task>> m_children;
    std::list<e172::ptr<Task>> m_trash;

public:
    typedef std::function<void(const e172::Variant&)> ResultHandleFunc;
private:
    std::list<ResultHandleFunc> m_onCompleatedSignal;

    e172::Variant m_resultValue;

    e172::SignalStreamBuffer m_outBuffer;
    std::ostream m_out = std::ostream(&m_outBuffer);
    void clearTrash();
public:
    std::ostream &out() { return m_out; };
    void connectToOut(const e172::SignalStreamBuffer::HandlerFunc& func);
    void connectToOut(std::ostream& stream);


    void completeTask(const e172::Variant &resultValue = e172::Variant());

    Task() = default;

    bool running() const { return m_running; }
    e172::ptr<Task> parentTask() const { return m_parentTask; }

    bool executeChildTask(const e172::ptr<Task>& task, e172::Context *context, const ResultHandleFunc& onCompleated = nullptr);

    void proceedBranch(e172::Context *context);
    virtual void proceed(e172::Context *context) = 0;
    virtual bool start(e172::Context *context) = 0;
    virtual void initFromCommand(const std::vector<std::string>&args, e172::Context *context) = 0;

    virtual ~Task();
    e172::ptr<Controller> parentController() const { return m_parentController; }
    e172::Variant resultValue() const { return m_resultValue; }
};

} // namespace proj172::core
