#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "capabilities/capability.h"
#include "units/ship.h"
#include "additional/trigger.h"

#include <engine/time/elapsedtimer.h>


class Controller : public Capability {    
protected:
    static const long ARMOR_RELEASE_DELAY;
    static const std::string ARMOR_RELEASE_MESSAGE;


    Ship *armor = nullptr;
    e172::ElapsedTimer *armorReleaseTimer = nullptr;
    Trigger armorReleaseMessageTrigger;

    Unit *selected = nullptr;

    void releaseArmor();
public:
    Controller();
    Controller(Ship *armor);

    virtual void onHit(e172::Context* context, int health);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
    void setSelected(Unit *value);
};

#endif // CONTROLLER_H
