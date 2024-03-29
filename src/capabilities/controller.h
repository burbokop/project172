#pragma once

#include "../additional/trigger.h"
#include "../tasks/task.h"
#include "capability.h"
#include <e172/time/elapsedtimer.h>

namespace proj172::core {

class Ship;
class Person;

class Controller : public Capability {    
    friend Task;
    e172::ElapsedTimer armorReleaseTimer = e172::ElapsedTimer(ARMOR_RELEASE_DELAY);
    e172::ptr<Ship> m_armor;
    bool releaseState = false;
    Trigger armorReleaseMessageTrigger;

    e172::ptr<Person> m_person;

    e172::ptr<Task> m_rootTask;
    std::list<e172::ptr<Task>> m_trash;
    void clearTrash();
protected:
    static const long ARMOR_RELEASE_DELAY;
    static const std::string ARMOR_RELEASE_MESSAGE;

    void releaseArmor();
public:
    Controller(e172::FactoryMeta &&meta)
        : Capability(std::move(meta))
    {}

    Controller(e172::FactoryMeta &&meta, const e172::ptr<Ship> &armor)
        : Capability(std::move(meta))
        , m_armor(armor)
    {}

    virtual void onHit(e172::Context* context, int health);

    e172::ptr<Ship> armor() const;
    void setArmor(const e172::ptr<Ship> &armor);
    e172::ptr<Person> person() const;
    void setPerson(const e172::ptr<Person> &person);

    bool executeRootTask(const e172::ptr<Task> &task, e172::Context *context, const Task::ResultHandleFunc &onCompleated = nullptr);
    e172::ptr<Task> rootTask() const;

    virtual ~Controller();

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler);
    void render(e172::Context *context, e172::AbstractRenderer *renderer);
};

} // namespace proj172::core
