#ifndef PLAYER_H
#define PLAYER_H


#include "capabilities/controller.h"


class Player : public Controller, public Loadable {
private:
    static const std::map<std::string, int> scancode;

    bool warpKeyPressed = false;
    std::map<std::string, int> personalScancode;
    bool getPersonalKey(Event *event, std::string id);

public:
    Player();
    Player(Loadable* tmp);
    void setArmor(Ship *armor);

    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(e172::AbstractRenderer *renderer);

    // Controller interface
public:
    void onHit(Context* context, int health);
};

#endif // PLAYER_H
