#include "task.h"

#include <src/capabilities/controller.h>

#include <src/debug.h>

bool Task::running() const {
    return m_running;
}

e172::ptr<Task> Task::parentTask() const {
    return m_parentTask;
}

bool Task::executeChildTask(const e172::ptr<Task> &task, e172::Context *context, const std::function<void ()> &onCompleated) {
    if(!task->m_parentTask) {
        if(m_children.insert(task).second) {
            task->m_parentTask = this;
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
    for(const auto &t : m_trash) {
        m_children.erase(t);
        t.safeDestroy();
    }
    m_trash.clear();
    for(const auto &c : m_children) {
        c->proceedBranch(context);
    }
    if(m_running) {
        proceed(context);
    }
}

Task::~Task() {
    for(const auto &t : m_trash) {
        t.safeDestroy();
    }
    for(const auto &c : m_children) {
        c.safeDestroy();
    }
}

e172::ptr<Controller> Task::parentController() const {
    return m_parentController;
}


void Task::completeTask() {
    if(m_running) {
        m_running = false;
        if(m_parentTask) {
            m_parentTask->m_trash.push_back(this);
            m_parentTask->m_running = true;
        } else if (m_parentController) {
            m_parentController->m_trash.push_back(this);
        }
        for(const auto& c : m_onCompleatedSignal) {
            if(c) {
                c();
            }
        }
        m_onCompleatedSignal.clear();
    }
}

Task::Task() {}
