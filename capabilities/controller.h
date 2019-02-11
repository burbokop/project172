#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "worker.h"
#include "capability.h"
#include "../units/ship.h"
#include "../additional/trigger.h"

class Controller : public Capability {    
protected:
    static const long ARMOR_RELEASE_DELAY;
    static const char *ARMOR_RELEASE_MESSAGE;


    Ship *armor = nullptr;
    Timer *armorReleaseTimer = nullptr;
    Trigger armorReleaseMessageTrigger;

    void releaseArmor();
public:
    Controller();
    Controller(Ship *armor);

    Unit *getParent();

    virtual void onHit(Context* context, int health);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // CONTROLLER_H
