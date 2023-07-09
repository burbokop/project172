#pragma once

#include <e172/entity.h>
#include <e172/math/vector.h>
#include <e172/time/elapsedtimer.h>

namespace proj172::core {

class LightParticle : public e172::Entity {
public:
    static const unsigned PIXEL;
    static const unsigned SQUARE;
    static const unsigned CIRCLE;

    static const int DEFAULT_AVERAGE_LIFE_TIME;
    static const int DEFAULT_LIFE_TIME_DELTA;

    static const double STOP_MOVING_VELOCITY;

public:
    LightParticle(e172::FactoryMeta &&meta,
                  unsigned shape = PIXEL,
                  int averageLifeTime = DEFAULT_AVERAGE_LIFE_TIME,
                  int lifeTimeDelta = DEFAULT_LIFE_TIME_DELTA);
    void place(e172::Vector<double> pos, e172::Vector<double> vel);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler);
    void render(e172::Context *context, e172::AbstractRenderer *renderer);

private:
    e172::Vector<double> m_pos;
    e172::Vector<double> m_vel;

    unsigned m_shape = PIXEL;
    int m_radius = 2;
    uint32_t m_color = 0xff00ff;
    e172::ElapsedTimer *m_destroyTimer = nullptr;
    double m_velocityMultiplier = 0;
};

} // namespace proj172::core
