#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>


#include <engine/entity.h>
#include <engine/time/elapsedtimer.h>
#include <src/engine/math/vector.h>
#include <units/movable.h>
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
    unsigned int amount;
    double slidingStart;

    e172::Vector m_lastResolution;

    e172::ElapsedTimer *flashingTimer = nullptr;
    Uint32 flashingColor = DEFAULT_FLASHING_COLOR;
    Uint32 colorBuffer = DEFAULT_MAIN_COLOR;
    int flashesRemains = 0;
    Movable *m_movable = nullptr;
    void onResolutionChanged(const e172::Vector &resolution);
public:
    Background(unsigned int amount, double slidingStart = STARS_SLIDING_SPEED);


    // Entity interface
public:
    void proceed(e172::Context *, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *renderer);
    void bindToMovable(Movable *value);

    void flashing(int repeats);
};

#endif // BACKGROUND_H
