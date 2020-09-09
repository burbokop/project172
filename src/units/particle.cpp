#include "particle.h"

#include <src/engine/context.h>
#include <src/engine/graphics/abstractrenderer.h>

const uint8_t Particle::PIXEL = 0;
const uint8_t Particle::SQUARE = 1;
const uint8_t Particle::CIRCLE = 2;

const int Particle::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int Particle::DEFAULT_LIFE_TIME_DELTA = 4000;

uint32_t Particle::generateColor() {
    uint32_t colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };
    return  colors[std::rand() % 4];
}

Particle::Particle() : Movable() {
    color = generateColor();
    setRelativisticVelocity(false);
    destroyTimer = new e172::ElapsedTimer((rand() % (2 * DEFAULT_LIFE_TIME_DELTA)) + (DEFAULT_AVERAGE_LIFE_TIME - DEFAULT_LIFE_TIME_DELTA));
    destroyTimer->reset();

}

Particle::Particle(uint8_t shape, int averageLifeTime, int lifeTimeDelta) {
    color = generateColor();
    this->shape = shape;
    setRelativisticVelocity(false);
    destroyTimer = new e172::ElapsedTimer((rand() % (2 * lifeTimeDelta)) + (averageLifeTime - lifeTimeDelta));
    destroyTimer->reset();
}


void Particle::render(e172::AbstractRenderer *renderer) {
    if(shape == PIXEL) {
        renderer->drawPixel(renderer->offset() + pos, color);
    } else if(shape == SQUARE) {
        renderer->drawSquare(renderer->offset() + pos, radius, color);
    } else if(shape == CIRCLE) {
        renderer->drawCircle(renderer->offset() + pos, radius, color);
    }
}

void Particle::hit(e172::Context *context, int value) {
    UNUSED(context);
    UNUSED(value);
}

void Particle::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(destroyTimer && destroyTimer->check()) {
        context->emitMessage(e172::Context::DESTROY_ENTITY, entityId());
    }
    this->Movable::proceed(context, eventHandler);
}
