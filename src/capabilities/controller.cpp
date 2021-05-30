#include "controller.h"

#include <src/args.h>
#include <src/context.h>
#include <src/units/ship.h>
#include <src/capabilities/docker.h>

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

bool Controller::executeRootTask(const e172::ptr<Task> &task, e172::Context *context) {
    if(!m_rootTask) {
        m_rootTask = task;
        m_rootTask->m_running = true;
        task->m_parentController = this;
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
    for(const auto &t : m_trash) {
        if(t == m_rootTask) {
            m_rootTask = nullptr;
        }
        t.safeDestroy();
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

Controller::Controller() {}

Controller::Controller(const e172::ptr<Ship> &armor) {
    m_armor = armor;
}

void Controller::onHit(e172::Context *context, int health) {
    UNUSED(context);
    UNUSED(health);
}

void Controller::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(eventHandler);
    if(armorReleaseMessageTrigger.check()) {
        context->emitMessage(e172::Context::EMERGENCY_MESSAGE, ARMOR_RELEASE_MESSAGE);
    }

    if(releaseState && armorReleaseTimer.check()) {
        if(m_armor && parentUnit()) {
            context->emitMessage(e172::Context::REMOVE_CAPABILITY, e172::VariantVector { parentUnit()->entityId(), entityId() });
            context->emitMessage(e172::Context::ADD_CAPABILITY, e172::VariantVector { m_armor->entityId(), entityId() });
            context->emitMessage(e172::Context::SPAWN_UNIT, e172::VariantVector { parentUnit()->entityId(), m_armor->entityId() });
            releaseState = false;
        }
    }

    for(const auto &t : m_trash) {
        t.safeDestroy();
    }
    m_trash.clear();

    if(m_rootTask) {
        m_rootTask->proceedBranch(context);
    }
}

void Controller::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}
