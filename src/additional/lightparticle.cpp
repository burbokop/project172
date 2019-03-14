#include "lightparticle.h"
#include "context.h"
#include "time/time.h"

const unsigned LightParticle::PIXEL = 0;
const unsigned LightParticle::SQUARE = 1;
const unsigned LightParticle::CIRCLE = 2;

const int LightParticle::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int LightParticle::DEFAULT_LIFE_TIME_DELTA = 4000;

const double LightParticle::STOP_MOVING_VELOCITY = 0.015;


LightParticle::LightParticle(unsigned shape, int averageLifeTime, int lifeTimeDelta) : Worker () {
    Uint32 colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };
    color = colors[std::rand() % 4];
    this->shape = shape;
    destroyTimer = new Timer(static_cast<unsigned>((rand() % (2 * lifeTimeDelta)) + (averageLifeTime - lifeTimeDelta)));
    destroyTimer->reset();
    velocityMultiplier = static_cast<double>((std::rand() % 4 + 3)) / 5;
}

void LightParticle::place(Vector pos, Vector vel) {
    this->pos = pos;
    this->vel = vel;
}


void LightParticle::tick(Context *context, Event *event) {
    UNUSED(event);
    if(destroyTimer && destroyTimer->count()) {
        context->addEvent(this, Context::DELETE_UNIT);
    }
    vel = vel * (1 - Time::getDeltaTime() * velocityMultiplier);

    //vel -= (vel * 1 * Time::getDeltaTime());

    pos += vel * Time::getDeltaTime() * 0.1;
}

void LightParticle::render(Renderer *renderer) {
    switch (shape) {
        case PIXEL: renderer->pixel(renderer->getOffset() + pos, color); break;
        case SQUARE: renderer->square(renderer->getOffset() + pos, radius, color); break;
        case CIRCLE: renderer->circle(renderer->getOffset() + pos, radius, color); break;
    }
}
