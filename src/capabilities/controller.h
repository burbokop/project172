#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "capability.h"
#include <src/units/ship.h>
#include <src/additional/trigger.h>

#include <src/engine/time/elapsedtimer.h>


class Controller : public Capability {    
protected:
    static const long ARMOR_RELEASE_DELAY;
    static const std::string ARMOR_RELEASE_MESSAGE;


    Ship *armor = nullptr;
    e172::ElapsedTimer *armorReleaseTimer = nullptr;
    Trigger armorReleaseMessageTrigger;

    e172::Entity::id_t m_selectedEntity = 0;

    void releaseArmor();
public:
    Controller();
    Controller(Ship *armor);

    virtual void onHit(e172::Context* context, int health);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
    e172::Entity::id_t selectedEntity() const;
    void setSelectedEntity(const e172::Entity::id_t &selectedEntity);
};

#endif // CONTROLLER_H
