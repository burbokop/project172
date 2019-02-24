#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>


#include "additional/vector.h"
#include "worker.h"
#include "additional/timer.h"


struct Star {
    Vector pos;
    Uint32 color;
};

class Background : public Worker {
private:
    static const double STARS_SLIDING_SPEED;
    static const Uint32 DEFAULT_MAIN_COLOR;
    static const Uint32 DEFAULT_FLASHING_COLOR;
    static const long DEFAULT_FLASHING_INTERVAL;


    Uint32 mainColor = DEFAULT_MAIN_COLOR;
    std::vector<Star> stars;
    Vector speed;
    unsigned int amount;
    double slidingStart;

    Vector resolution;
    Timer observer = Timer(4000);


    Timer *flashingTimer = nullptr;
    Uint32 flashingColor = DEFAULT_FLASHING_COLOR;
    Uint32 colorBuffer = DEFAULT_MAIN_COLOR;
    int flashesRemains = 0;

public:
    Background();
    void init(Vector resolution, unsigned int amount, double slidingStart = STARS_SLIDING_SPEED);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer);
    void setSpeed(const Vector &value);

    void flashing(int repeats);
};

#endif // BACKGROUND_H
