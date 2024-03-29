#include "controller.h"
#include "../messagetype.h"

#include "../capabilities/docker.h"
#include "../units/ship.h"
#include <e172/args.h>
#include <e172/context.h>

namespace proj172::core {

const long Controller::ARMOR_RELEASE_DELAY = 1000;
const std::string Controller::ARMOR_RELEASE_MESSAGE = "emergency catapult";

e172::ptr<Ship> Controller::armor() const {
    return m_armor;
}

void Controller::setArmor(const e172::ptr<Ship> &armor) {
    m_armor = armor;
}

e172::ptr<Person> Controller::person() const {
    return m_person;
}

void Controller::setPerson(const e172::ptr<Person> &person) {
    m_person = person;
}

bool Controller::executeRootTask(const e172::ptr<Task> &task, e172::Context *context, const Task::ResultHandleFunc &onCompleated) {
    if(!m_rootTask) {
        m_rootTask = task;
        m_rootTask->m_running = true;
        task->m_parentController = this;
        if(onCompleated) {
            task->m_onCompleatedSignal.push_back(onCompleated);
        }
        if(m_rootTask->start(context)) {
            return true;
        } else {
            m_trash.push_back(task);
        }
    }
    return false;
}

e172::ptr<Task> Controller::rootTask() const {
    return m_rootTask;
}

Controller::~Controller() {
    clearTrash();
}

void Controller::clearTrash() {
    for(const auto &t : m_trash) {
        if(t == m_rootTask) {
            m_rootTask = nullptr;
        }
        for(const auto& c : t->m_onCompleatedSignal) {
            if(c) {
                c(t->resultValue());
            }
        }
        t->m_onCompleatedSignal.clear();
        t.destroy();
    }
    m_trash.clear();
}

void Controller::releaseArmor() {
    if(m_armor && parentUnit() && m_armor != parentUnit()) {
        armorReleaseTimer.reset();
        releaseState = true;
        armorReleaseMessageTrigger.enable();
    }
}

void Controller::onHit(e172::Context *context, int health) {
    UNUSED(context);
    UNUSED(health);
}

void Controller::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    UNUSED(eventHandler);
    if(armorReleaseMessageTrigger.check()) {
        context->emitMessage(~MessageType::EmergencyMessage, ARMOR_RELEASE_MESSAGE);
    }

    if(releaseState && armorReleaseTimer.check()) {
        if(m_armor && parentUnit()) {
            context->emitMessage(~MessageType::RemoveCapability,
                                 e172::VariantVector{parentUnit()->entityId(), entityId()});
            context->emitMessage(~MessageType::AddCapability,
                                 e172::VariantVector{m_armor->entityId(), entityId()});
            context->emitMessage(~MessageType::SpawnUnit,
                                 e172::VariantVector{parentUnit()->entityId(), m_armor->entityId()});
            releaseState = false;
        }
    }

    clearTrash();

    if(m_rootTask) {
        m_rootTask->proceedBranch(context);
    }
}

void Controller::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    UNUSED(renderer);
}

} // namespace proj172::core
