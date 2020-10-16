#ifndef LIGHTPARTICLE_H
#define LIGHTPARTICLE_H

#include <src/entity.h>
#include <src/math/vector.h>
#include <src/time/elapsedtimer.h>


class LightParticle : public e172::Entity {
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
    uint32_t color = 0xff00ff;
    e172::ElapsedTimer *destroyTimer = nullptr;
    double velocityMultiplier = 0;


public:
    LightParticle(unsigned shape = PIXEL, int averageLifeTime = DEFAULT_AVERAGE_LIFE_TIME, int lifeTimeDelta = DEFAULT_LIFE_TIME_DELTA);
    void place(e172::Vector pos, e172::Vector vel);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // LIGHTPARTICLE_H
