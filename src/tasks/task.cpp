#include "task.h"

#include "../capabilities/controller.h"
#include <e172/debug.h>

namespace proj172::core {

bool Task::executeChildTask(const e172::ptr<Task> &task,
                            e172::Context *context,
                            const ResultHandleFunc &onCompleated)
{
    if(!task->m_parentTask) {
        if(m_children.insert(task).second) {
            task->m_parentTask = this;
            task->connectToOut(m_out);
            task->m_parentController = this->m_parentController;
            this->m_running = false;
            task->m_running = true;
            if(onCompleated) {
                task->m_onCompleatedSignal.push_back(onCompleated);
            }
            task->start(context);
            return true;
        }
    }
    return false;
}

void Task::proceedBranch(e172::Context *context) {
    clearTrash();
    for(const auto &c : m_children) {
        c->proceedBranch(context);
    }
    if(m_running) {
        proceed(context);
    }
}

Task::~Task() {
    clearTrash();
    for(const auto &c : m_children) {
        c.destroy();
    }
}

void Task::clearTrash()
{
    for(const auto &t : m_trash) {
        m_children.erase(t);
        for(const auto& c : t->m_onCompleatedSignal) {
            if(c) {
                c(m_resultValue);
            }
        }
        t->m_onCompleatedSignal.clear();
        t.destroy();
    }
    m_trash.clear();
}

void Task::connectToOut(const e172::SignalStreamBuffer::HandlerFunc &func) {
    m_outBuffer.connect(func);
}

void Task::connectToOut(std::ostream &stream) {
    m_outBuffer.connect(stream);
}

void Task::completeTask(const e172::Variant& resultValue) {
    if(m_running) {
        m_running = false;
        m_resultValue = resultValue;
        if(m_parentTask) {
            m_parentTask->m_trash.push_back(this);
            m_parentTask->m_running = true;
        } else if (m_parentController) {
            m_parentController->m_trash.push_back(this);
        }        
    }
}

} // namespace proj172::core
