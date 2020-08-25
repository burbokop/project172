#ifndef PLAYER_H
#define PLAYER_H


#include "controller.h"

#include <src/engine/abstracteventhandler.h>


class Player : public Controller, public e172::Loadable {
private:
    static const std::map<std::string, e172::Scancode> scancode;

    bool warpKeyPressed = false;
    std::map<std::string, e172::Scancode> personalScancode;
    bool getPersonalKey(e172::AbstractEventHandler *eventHandler, std::string id);

public:
    Player();
    Player(Loadable* tmp);
    void setArmor(Ship *armor);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

    // Controller interface
public:
    void onHit(e172::Context* context, int);
};

#endif // PLAYER_H
