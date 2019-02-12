#include "background.h"
#include "context.h"

const double Background::STARS_SLIDING_SPEED = 12;
const Uint32 Background::DEFAULT_MAIN_COLOR = 0x333353;
const Uint32 Background::DEFAULT_FLASHING_COLOR = 0xff0000;
const long Background::DEFAULT_FLASHING_INTERVAL = 32;



void Background::setSpeed(const Vector &value) {
    speed = value;
}

void Background::flashing(int repeats) {
    flashingTimer = new Timer(DEFAULT_FLASHING_INTERVAL);
    flashingTimer->reset();
    flashesRemains = repeats;
}

Background::Background() {
}

void Background::init(Vector resolution, unsigned int amount, double slidingStart) {
    this->resolution = resolution;
    this->slidingStart = slidingStart;
    this->amount = amount;
    Uint32 colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };

    stars.clear();
    for(unsigned int i = 0; i < amount; i++) {
        Star star;
        star.color = colors[std::rand() % 4];
        star.pos = Vector(std::rand() % resolution.getIntX(), std::rand() % resolution.getIntY());
        stars.push_back(star);
    }
}

void Background::loop(Context *context, Event *event) {
    UNUSED(context);
    UNUSED(event);
}

void Background::render(Renderer *renderer) {
    if(observer.count(true)) {
        if(resolution != renderer->getResolution()) {
            init(renderer->getResolution(), amount, slidingStart);
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
        Vector localOffset = renderer->getOffset() * -0.4;

        for(Star star : stars) {
            int x = star.pos.getIntX() - localOffset.getIntX();
            if(x >= 0) x = x % renderer->getResolution().getIntX();
            else x = x % renderer->getResolution().getIntX() + renderer->getResolution().getIntX();

            int y = star.pos.getIntY() - localOffset.getIntY();
            if(y >= 0) y = y % renderer->getResolution().getIntY();
            else y = y % renderer->getResolution().getIntY() + renderer->getResolution().getIntY();

            if(speed.module() < slidingStart) {
                renderer->pixel(Vector(x, y), star.color);
            } else {
                renderer->line(Vector(x, y), Vector(x, y) - (speed - slidingStart), star.color);
            }
        }
    }
}
