#include "lightparticle.h"

#include <inttypes.h>

#include <src/engine/context.h>

#include <src/engine/graphics/abstractrenderer.h>

//#include <vulkan/vulkan_intel.h>

const unsigned LightParticle::PIXEL = 0;
const unsigned LightParticle::SQUARE = 1;
const unsigned LightParticle::CIRCLE = 2;

const int LightParticle::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int LightParticle::DEFAULT_LIFE_TIME_DELTA = 4000;

const double LightParticle::STOP_MOVING_VELOCITY = 0.015;


LightParticle::LightParticle(unsigned shape, int averageLifeTime, int lifeTimeDelta) : e172::Entity () {
    uint32_t colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };
    color = colors[std::rand() % 4];
    this->shape = shape;
    destroyTimer = new e172::ElapsedTimer(static_cast<unsigned>((rand() % (2 * lifeTimeDelta)) + (averageLifeTime - lifeTimeDelta)));
    destroyTimer->reset();
    velocityMultiplier = static_cast<double>((std::rand() % 4 + 3)) / 5;
}

void LightParticle::place(e172::Vector pos, e172::Vector vel) {
    this->pos = pos;
    this->vel = vel;
}


void LightParticle::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(eventHandler);
    if(destroyTimer && destroyTimer->check()) {
        context->emitMessage(e172::Context::DELETE_UNIT, entityId());
    }
    vel = vel * (1 - context->deltaTime() * velocityMultiplier);

    //vel -= (vel * 1 * context->deltaTime());

    pos += vel * context->deltaTime() * 0.1;
}

void LightParticle::render(e172::AbstractRenderer *renderer) {
    switch (shape) {
        case PIXEL: renderer->drawPixel(renderer->offset() + pos, color); break;
        case SQUARE: renderer->drawSquare(renderer->offset() + pos, radius / 2, color); break;
        case CIRCLE: renderer->drawCircle(renderer->offset() + pos, radius, color); break;
    }
}
