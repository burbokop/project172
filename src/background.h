#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <src/entity.h>
#include <src/physicalobject.h>
#include <src/time/elapsedtimer.h>
#include <src/math/vector.h>
#include <vector>


struct Star {
    e172::Vector pos;
    uint32_t color;
};

class Background : public e172::Entity {
    static const double STARS_SLIDING_SPEED;
    static const double SLIDING_LEGHTH;
    static const uint32_t DEFAULT_MAIN_COLOR;
    static const uint32_t DEFAULT_FLASHING_COLOR;
    static const long DEFAULT_FLASHING_INTERVAL;



    uint32_t mainColor = DEFAULT_MAIN_COLOR;
    std::vector<Star> stars;
    unsigned int amount;
    double slidingStart;

    e172::Vector m_lastResolution;

    e172::ElapsedTimer flashingTimer = e172::ElapsedTimer(DEFAULT_FLASHING_INTERVAL);
    uint32_t flashingColor = DEFAULT_FLASHING_COLOR;
    uint32_t colorBuffer = DEFAULT_MAIN_COLOR;
    int flashesRemains = 0;
    e172::PhysicalObject *m_physicalObject = nullptr;
    void onResolutionChanged(const e172::Vector &resolution);
public:
    Background(unsigned int amount, double slidingStart = STARS_SLIDING_SPEED);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *renderer);
    void bindToPhysicalObject(e172::PhysicalObject *value);

    void flashing(e172::Context *, const e172::Variant &repeats);
    void flashing(const int &repeats);
};

#endif // BACKGROUND_H
