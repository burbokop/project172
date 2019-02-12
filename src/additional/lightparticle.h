#ifndef LIGHTPARTICLE_H
#define LIGHTPARTICLE_H

#include "../worker.h"
#include "timer.h"

class LightParticle : public Worker {
public:
    static const Uint8 PIXEL;
    static const Uint8 SQUARE;
    static const Uint8 CIRCLE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;

    static const double STOP_MOVING_VELOCITY;


private:
    Vector pos;
    Vector vel;

    Uint8 shape = PIXEL;
    int radius = 2;
    Uint32 color = 0xff00ff;
    Timer destroyTimer = Timer((rand() % (2 * DEFAULT_LIFE_TIME_DELTA)) + (DEFAULT_AVERAGE_LIFE_TIME - DEFAULT_LIFE_TIME_DELTA));
    double velocityMultiplier = 0;


public:
    LightParticle(Uint8 shape = PIXEL);
    void place(Vector pos, Vector vel);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // LIGHTPARTICLE_H
