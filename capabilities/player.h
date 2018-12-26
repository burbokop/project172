#ifndef PLAYER_H
#define PLAYER_H

#include "controller.h"
#include "./modules/weapon.h"

class Player : public Controller {
private:
    bool warpKeyPressed = false;

public:
    Player();

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // PLAYER_H
