#ifndef PARTICLE_H
#define PARTICLE_H


#include "movable.h"


class Particle : public Movable {
public:
    static const uint8_t PIXEL;
    static const uint8_t SQUARE;
    static const uint8_t CIRCLE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;


private:
    uint8_t shape = PIXEL;
    int radius = 2;
    uint32_t color = 0xff00ff;
    uint32_t generateColor();
    e172::ElapsedTimer *destroyTimer = nullptr;

public:
    Particle();
    Particle(uint8_t shape, int averageLifeTime = DEFAULT_AVERAGE_LIFE_TIME, int lifeTimeDelta = DEFAULT_LIFE_TIME_DELTA);

    // Entity interface
public:
    void render(e172::AbstractRenderer *renderer);

    // Unit interface
public:
    void hit(e172::Context *context, int value);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
};

#endif // PARTICLE_H
