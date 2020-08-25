#include "background.h"

#include <src/engine/time/elapsedtimer.h>
#include <src/engine/graphics/abstractrenderer.h>
#include <src/engine/context.h>



const double Background::STARS_SLIDING_SPEED = 400.0;
const double Background::SLIDING_LEGHTH = 0.05;
const uint32_t Background::DEFAULT_MAIN_COLOR = 0x333353;
const uint32_t Background::DEFAULT_FLASHING_COLOR = 0xff0000;
const long Background::DEFAULT_FLASHING_INTERVAL = 32;


void Background::flashing(int repeats) {
    flashingTimer.reset();
    flashesRemains = repeats;
}

Background::Background(unsigned int amount, double slidingStart) {
    this->slidingStart = slidingStart;
    this->amount = amount;
}

void Background::onResolutionChanged(const e172::Vector &resolution) {
    uint32_t colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };

    stars.clear();
    for(unsigned int i = 0; i < amount; i++) {
        Star star;
        star.color = colors[std::rand() % 4];
        star.pos = e172::Vector(std::rand() % resolution.intX(), std::rand() % resolution.intY());
        stars.push_back(star);
    }
}
void Background::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    bool ok = false;
    const auto value = context->popMessage(e172::Context::BACKGROUND_FLASHING, &ok);
    if(ok) {
        flashing(value.toInt());
    }
}

void Background::render(e172::AbstractRenderer *renderer) {
    const auto resolution = renderer->resolution();
    if(m_lastResolution != resolution) {
        onResolutionChanged(resolution);
        m_lastResolution = resolution;
    }

    if(flashesRemains >= 0 && flashingTimer.check()) {
        if(mainColor != flashingColor) {
            colorBuffer = mainColor;
            mainColor = flashingColor;
        } else {
            mainColor = colorBuffer;
        }

        if(flashesRemains <= 0) {
            mainColor = colorBuffer;
        }
        flashesRemains--;
    }

    if(renderer) {
        renderer->fill(mainColor);
        e172::Vector localOffset = renderer->offset() * -0.4;

        for(Star star : stars) {
            int x = star.pos.intX() - localOffset.intX();
            if(x >= 0) x = x % resolution.intX();
            else x = x % resolution.intX() + resolution.intX();

            int y = star.pos.intY() - localOffset.intY();
            if(y >= 0) y = y % resolution.intY();
            else y = y % resolution.intY() + resolution.intY();

            e172::Vector velocity;
            if(m_movable)
                velocity = m_movable->velocity();

            if(velocity.module() < slidingStart) {
                renderer->drawPixel(e172::Vector(x, y), star.color);
            } else {
                renderer->drawLine(e172::Vector(x, y), e172::Vector(x, y) - (velocity - slidingStart) * SLIDING_LEGHTH, star.color);
            }
        }
    }
}

void Background::bindToMovable(Movable *value) {
    m_movable = value;
}
