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
    setRelativisticVelocity(false);
    destroyTimer = new Timer((rand() % (2 * DEFAULT_LIFE_TIME_DELTA)) + (DEFAULT_AVERAGE_LIFE_TIME - DEFAULT_LIFE_TIME_DELTA));
    destroyTimer->reset();

}

Particle::Particle(Uint8 shape, int averageLifeTime, int lifeTimeDelta) {
    color = generateColor();
    this->shape = shape;
    setRelativisticVelocity(false);
    destroyTimer = new Timer((rand() % (2 * lifeTimeDelta)) + (averageLifeTime - lifeTimeDelta));
    destroyTimer->reset();
}

Particle::Particle(Loadable *tmp) : Movable (tmp) {
    color = generateColor();
    setRelativisticVelocity(false);
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

void Particle::hit(Context *context, int value) {
    UNUSED(context);
    UNUSED(value);
}

void Particle::tick(Context *context, Event *event) {
    if(destroyTimer && destroyTimer->count()) {
        context->addEvent(this, Context::DELETE_UNIT);
    }
    this->Movable::tick(context, event);
}
