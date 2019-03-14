#ifndef PARTICLE_H
#define PARTICLE_H


#include "units/movable.h"


class Particle : public Movable {
public:
    static const Uint8 PIXEL;
    static const Uint8 SQUARE;
    static const Uint8 CIRCLE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;


private:
    Uint8 shape = PIXEL;
    int radius = 2;
    Uint32 color = 0xff00ff;
    Uint32 generateColor();
    Timer *destroyTimer = nullptr;

public:
    Particle();
    Particle(Uint8 shape, int averageLifeTime = DEFAULT_AVERAGE_LIFE_TIME, int lifeTimeDelta = DEFAULT_LIFE_TIME_DELTA);
    Particle(Loadable *tmp);

    // Worker interface
public:
    void render(Renderer *renderer);

    // Unit interface
public:
    void hit(Context *context, int value);

    // Worker interface
public:
    void tick(Context *context, Event *event);
};

#endif // PARTICLE_H
