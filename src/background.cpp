#include "background.h"
#include "context.h"



const double Background::STARS_SLIDING_SPEED = 400.0;
const double Background::SLIDING_LEGHTH = 0.05;
const Uint32 Background::DEFAULT_MAIN_COLOR = 0x333353;
const Uint32 Background::DEFAULT_FLASHING_COLOR = 0xff0000;
const long Background::DEFAULT_FLASHING_INTERVAL = 32;



void Background::setSpeed(const e172::Vector &value) {
    speed = value;
}

void Background::flashing(int repeats) {
    flashingTimer = new Timer(DEFAULT_FLASHING_INTERVAL);
    flashingTimer->reset();
    flashesRemains = repeats;
}

Background::Background(e172::Vector resolution, unsigned int amount, double slidingStart) {
    this->slidingStart = slidingStart;
    this->amount = amount;
    onResolutionChange(resolution);
}

void Background::onResolutionChange(e172::Vector resolution) {
    this->resolution = resolution;
    Uint32 colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };

    stars.clear();
    for(unsigned int i = 0; i < amount; i++) {
        Star star;
        star.color = colors[std::rand() % 4];
        star.pos = e172::Vector(std::rand() % resolution.intX(), std::rand() % resolution.intY());
        stars.push_back(star);
    }
}

void Background::tick(Context *context, Event *event) {
    UNUSED(context);
    UNUSED(event);
}

void Background::render(e172::AbstractRenderer *renderer) {
    if(observer.count(true)) {
        if(resolution != renderer->resolution()) {
            onResolutionChange(renderer->resolution());
        }
    }

    if(flashingTimer && flashingTimer->count()) {
        if(mainColor != flashingColor) {
            colorBuffer = mainColor;
            mainColor = flashingColor;
        } else {
            mainColor = colorBuffer;
        }

        if(flashesRemains <= 0) {
            flashingTimer = nullptr;
            mainColor = colorBuffer;
        }
        flashesRemains--;
    }

    if(renderer) {
        renderer->fill(mainColor);
        e172::Vector localOffset = renderer->offset() * -0.4;

        for(Star star : stars) {
            int x = star.pos.intX() - localOffset.intX();
            if(x >= 0) x = x % renderer->resolution().intX();
            else x = x % renderer->resolution().intX() + renderer->resolution().intX();

            int y = star.pos.intY() - localOffset.intY();
            if(y >= 0) y = y % renderer->resolution().intY();
            else y = y % renderer->resolution().intY() + renderer->resolution().intY();

            if(speed.module() < slidingStart) {
                renderer->drawPixel(e172::Vector(x, y), star.color);
            } else {
                renderer->drawLine(e172::Vector(x, y), e172::Vector(x, y) - (speed - slidingStart) * SLIDING_LEGHTH, star.color);
            }
        }
    }
}
