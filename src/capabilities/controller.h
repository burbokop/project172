#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "capability.h"

#include <src/additional/trigger.h>

#include <src/time/elapsedtimer.h>

#include <src/persons/person.h>

class Ship;
class Controller : public Capability {    
    e172::ElapsedTimer armorReleaseTimer = e172::ElapsedTimer(ARMOR_RELEASE_DELAY);
    e172::ptr<Ship> m_armor;
    bool releaseState = false;
    Trigger armorReleaseMessageTrigger;

    e172::ptr<Person> m_person;

protected:
    static const long ARMOR_RELEASE_DELAY;
    static const std::string ARMOR_RELEASE_MESSAGE;

    void releaseArmor();
public:
    Controller();
    Controller(const e172::ptr<Ship> &armor);

    virtual void onHit(e172::Context* context, int health);

    e172::ptr<Ship> armor() const;
    void setArmor(const e172::ptr<Ship> &armor);
    e172::ptr<Person> person() const;
    void setPerson(const e172::ptr<Person> &person);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // CONTROLLER_H
