#include "background.h"

#include "src/messagetype.h"
#include <src/context.h>
#include <src/debug.h>
#include <src/graphics/abstractrenderer.h>
#include <src/time/elapsedtimer.h>

namespace proj172::core {

const double Background::STARS_SLIDING_SPEED = 400.0;
const double Background::SLIDING_LEGHTH = 0.05;
const std::uint32_t Background::DEFAULT_MAIN_COLOR = 0x333353;
const std::uint32_t Background::DEFAULT_FLASHING_COLOR = 0xff0000;
const long Background::DEFAULT_FLASHING_INTERVAL = 32;

void Background::flashing(const int &repeats) {
    m_flashingTimer.reset();
    m_flashesRemains = repeats;
}

void Background::flashing(e172::Context *, const e172::Variant &repeats) {
    m_flashingTimer.reset();
    m_flashesRemains = repeats.toInt();
}

Background::Background(e172::FactoryMeta &&meta, unsigned int amount, double slidingStart)
    : e172::Entity(std::move(meta))
    , m_slidingStart(slidingStart)
    , m_amount(amount)
{
    setDepth(-100);
}

void Background::onResolutionChanged(const e172::Vector<double> &resolution)
{
    uint32_t colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };

    m_stars.clear();
    for (unsigned int i = 0; i < m_amount; i++) {
        Star star;
        star.color = colors[std::rand() % 4];
        star.pos = e172::Vector<double>(std::rand() % resolution.intX(),
                                        std::rand() % resolution.intY());
        m_stars.push_back(star);
    }
}

void Background::proceed(e172::Context *context, e172::EventHandler *) {
    context->popMessage(~MessageType::BackgroundFlashing, this, &Background::flashing);
}

void Background::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    const auto resolution = renderer->resolution();
    if(m_lastResolution != resolution) {
        onResolutionChanged(resolution);
        m_lastResolution = resolution;
    }

    if (m_flashesRemains >= 0 && m_flashingTimer.check()) {
        if (m_mainColor != m_flashingColor) {
            m_colorBuffer = m_mainColor;
            m_mainColor = m_flashingColor;
        } else {
            m_mainColor = m_colorBuffer;
        }

        if (m_flashesRemains <= 0) {
            m_mainColor = m_colorBuffer;
        }
        m_flashesRemains--;
    }

    if(renderer) {
        renderer->fill(m_mainColor);
        e172::Vector localOffset = renderer->offset() * -0.4;

        for (Star star : m_stars) {
            int x = star.pos.intX() - localOffset.intX();
            if(x >= 0) x = x % resolution.intX();
            else x = x % resolution.intX() + resolution.intX();

            int y = star.pos.intY() - localOffset.intY();
            if(y >= 0) y = y % resolution.intY();
            else
                y = y % resolution.intY() + resolution.intY();

            e172::Vector<double> velocity;
            if(m_physicalObject)
                velocity = m_physicalObject->velocity();

            if (velocity.module() < m_slidingStart) {
                renderer->drawPixel(e172::Vector<double>(x, y), star.color);
            } else {
                renderer->drawLine(e172::Vector<double>(x, y),
                                   e172::Vector<double>(x, y)
                                       - (velocity - m_slidingStart) * SLIDING_LEGHTH,
                                   star.color);
            }
        }
    }
}

void Background::bindToPhysicalObject(e172::PhysicalObject *value) {
    m_physicalObject = value;
}

} // namespace proj172::core
