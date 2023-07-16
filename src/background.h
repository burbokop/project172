#pragma once

#include <e172/entity.h>
#include <e172/math/physicalobject.h>
#include <e172/math/vector.h>
#include <e172/time/elapsedtimer.h>
#include <vector>

namespace proj172::core {

struct Star {
    e172::Vector<double> pos;
    uint32_t color;
};

class Background : public e172::Entity
{
public:
    Background(e172::FactoryMeta &&meta,
               unsigned int amount,
               double slidingStart = STARS_SLIDING_SPEED);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *) override;
    void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
    void bindToPhysicalObject(e172::PhysicalObject *value);

    void flashing(e172::Context *, const e172::Variant &repeats);
    void flashing(const int &repeats);

private:
    void onResolutionChanged(const e172::Vector<std::uint32_t> &resolution);

private:
    static const double STARS_SLIDING_SPEED;
    static const double SLIDING_LEGHTH;
    static const uint32_t DEFAULT_MAIN_COLOR;
    static const uint32_t DEFAULT_FLASHING_COLOR;
    static const long DEFAULT_FLASHING_INTERVAL;

    uint32_t m_mainColor = DEFAULT_MAIN_COLOR;
    std::vector<Star> m_stars;
    unsigned int m_amount;
    double m_slidingStart;
    e172::Vector<std::uint32_t> m_lastResolution;
    e172::ElapsedTimer m_flashingTimer = e172::ElapsedTimer(DEFAULT_FLASHING_INTERVAL);
    uint32_t m_flashingColor = DEFAULT_FLASHING_COLOR;
    uint32_t m_colorBuffer = DEFAULT_MAIN_COLOR;
    int m_flashesRemains = 0;
    e172::PhysicalObject *m_physicalObject = nullptr;
};

} // namespace proj172::core
