#ifndef PLAYER_H
#define PLAYER_H


#include "capabilities/controller.h"


class Player : public Controller, public Loadable {
private:
    static const std::map<std::string, e172::Scancode> scancode;

    bool warpKeyPressed = false;
    std::map<std::string, e172::Scancode> personalScancode;
    bool getPersonalKey(e172::AbstractEventHandler *eventHandler, std::string id);

public:
    Player();
    Player(Loadable* tmp);
    void setArmor(Ship *armor);

    // Worker interface
public:
    void tick(Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

    // Controller interface
public:
    void onHit(Context* context, int health);
};

#endif // PLAYER_H
