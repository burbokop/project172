#ifndef PLAYER_H
#define PLAYER_H

#include "controller.h"

class Player : public Controller {
private:
    bool forwardKeyPressed = false;

public:
    Player();

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // PLAYER_H
