#ifndef LIGHTPARTICLE_H
#define LIGHTPARTICLE_H


#include "worker.h"
#include "time/timer.h"


class LightParticle : public Worker {
public:
    static const unsigned PIXEL;
    static const unsigned SQUARE;
    static const unsigned CIRCLE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;

    static const double STOP_MOVING_VELOCITY;


private:
    e172::Vector pos;
    e172::Vector vel;

    unsigned shape = PIXEL;
    int radius = 2;
    Uint32 color = 0xff00ff;
    Timer *destroyTimer = nullptr;
    double velocityMultiplier = 0;


public:
    LightParticle(unsigned shape = PIXEL, int averageLifeTime = DEFAULT_AVERAGE_LIFE_TIME, int lifeTimeDelta = DEFAULT_LIFE_TIME_DELTA);
    void place(e172::Vector pos, e172::Vector vel);

    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(e172::AbstractRenderer *renderer);
};

#endif // LIGHTPARTICLE_H
