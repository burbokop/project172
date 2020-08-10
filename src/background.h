#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>


#include <src/engine/math/vector.h>
#include "worker.h"
#include "time/timer.h"
#include <vector>


struct Star {
    e172::Vector pos;
    Uint32 color;
};

class Background : public Worker {
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
    Timer observer = Timer(4000);


    Timer *flashingTimer = nullptr;
    Uint32 flashingColor = DEFAULT_FLASHING_COLOR;
    Uint32 colorBuffer = DEFAULT_MAIN_COLOR;
    int flashesRemains = 0;

    void onResolutionChange(e172::Vector resolution);
public:
    Background(e172::Vector resolution, unsigned int amount, double slidingStart = STARS_SLIDING_SPEED);


    // Worker interface
public:
    void tick(Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
    void setSpeed(const e172::Vector &value);

    void flashing(int repeats);
};

#endif // BACKGROUND_H
