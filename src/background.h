#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>


#include <engine/entity.h>
#include <engine/time/elapsedtimer.h>
#include <src/engine/math/vector.h>
#include <vector>


struct Star {
    e172::Vector pos;
    Uint32 color;
};

class Background : public e172::Entity {
private:
    static const double STARS_SLIDING_SPEED;
    static const double SLIDING_LEGHTH;
    static const Uint32 DEFAULT_MAIN_COLOR;
    static const Uint32 DEFAULT_FLASHING_COLOR;
    static const long DEFAULT_FLASHING_INTERVAL;


    Uint32 mainColor = DEFAULT_MAIN_COLOR;
    std::vector<Star> stars;
    e172::Vector speed;
    unsigned int amount;
    double slidingStart;

    e172::Vector resolution;
    e172::ElapsedTimer observer = e172::ElapsedTimer(4000);


    e172::ElapsedTimer *flashingTimer = nullptr;
    Uint32 flashingColor = DEFAULT_FLASHING_COLOR;
    Uint32 colorBuffer = DEFAULT_MAIN_COLOR;
    int flashesRemains = 0;

    void onResolutionChange(e172::Vector resolution);
public:
    Background(e172::Vector resolution, unsigned int amount, double slidingStart = STARS_SLIDING_SPEED);


    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
    void setSpeed(const e172::Vector &value);

    void flashing(int repeats);
};

#endif // BACKGROUND_H
