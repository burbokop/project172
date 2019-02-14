#include "lightparticle.h"
#include "../context.h"

const Uint8 LightParticle::PIXEL = 0;
const Uint8 LightParticle::SQUARE = 1;
const Uint8 LightParticle::CIRCLE = 2;

const int LightParticle::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int LightParticle::DEFAULT_LIFE_TIME_DELTA = 4000;

const double LightParticle::STOP_MOVING_VELOCITY = 0.015;


LightParticle::LightParticle(Uint8 shape, int averageLifeTime, int lifeTimeDelta) : Worker () {
    Uint32 colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };
    color = colors[std::rand() % 4];
    this->shape = shape;
    destroyTimer = new Timer((rand() % (2 * lifeTimeDelta)) + (averageLifeTime - lifeTimeDelta));
    destroyTimer->reset();
    velocityMultiplier = static_cast<double>((std::rand() % 3 + 96)) / 100;
}

void LightParticle::place(Vector pos, Vector vel) {
    this->pos = pos;
    this->vel = vel;
}


void LightParticle::loop(Context *context, Event *event) {
    UNUSED(event);
    if(destroyTimer && destroyTimer->count()) {
        context->addEvent(this, Context::DELETE_UNIT);
    }
    vel *= velocityMultiplier;
    pos += vel;
}

void LightParticle::render(Renderer *renderer) {
    if(shape == PIXEL) {
        renderer->pixel(renderer->getOffset() + pos, color);
    } else if(shape == SQUARE) {
        renderer->square(renderer->getOffset() + pos, radius, color);
    } else if(shape == CIRCLE) {
        renderer->circle(renderer->getOffset() + pos, radius, color);
    }
}
