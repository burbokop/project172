#include "particle.h"
#include "context.h"


const Uint8 Particle::PIXEL = 0;
const Uint8 Particle::SQUARE = 1;
const Uint8 Particle::CIRCLE = 2;

const int Particle::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int Particle::DEFAULT_LIFE_TIME_DELTA = 4000;

Uint32 Particle::generateColor() {
    Uint32 colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };
    return  colors[std::rand() % 4];
}

Particle::Particle() : Movable() {
    color = generateColor();
    relativisticVelocity = false;
    destroyTimer.reset();
}

Particle::Particle(Uint8 shape) {
    color = generateColor();
    this->shape = shape;
    relativisticVelocity = false;
    destroyTimer.reset();
}

Particle::Particle(Loadable *tmp) : Movable (tmp) {
    color = generateColor();
    relativisticVelocity = false;
    destroyTimer.reset();
}

#include <iostream>
void Particle::render(Renderer *renderer) {
    std::cout << "render particle\n";
    if(shape == PIXEL) {
        std::cout << "     (pixel)\n";

        renderer->pixel(renderer->getOffset() + pos, color);
    } else if(shape == SQUARE) {
        renderer->square(renderer->getOffset() + pos, radius, color);
    } else if(shape == CIRCLE) {
        renderer->circle(renderer->getOffset() + pos, radius, color);
    }
}

void Particle::hit(Context *context, int value) {}

void Particle::loop(Context *context, Event *event) {
    if(destroyTimer.count(true)) {
        context->addEvent(this, Context::DELETE_UNIT);
    }
    this->Movable::loop(context, event);
}
