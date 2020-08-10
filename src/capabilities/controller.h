#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "capabilities/capability.h"
#include "time/timer.h"
#include "units/ship.h"
#include "additional/trigger.h"


class Controller : public Capability {    
protected:
    static const long ARMOR_RELEASE_DELAY;
    static const char *ARMOR_RELEASE_MESSAGE;


    Ship *armor = nullptr;
    Timer *armorReleaseTimer = nullptr;
    Trigger armorReleaseMessageTrigger;

    Unit *selected = nullptr;

    void releaseArmor();
public:
    Controller();
    Controller(Ship *armor);

    virtual void onHit(Context* context, int health);

    // Worker interface
public:
    void tick(Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
    void setSelected(Unit *value);
};

#endif // CONTROLLER_H
