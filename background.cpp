#include "background.h"


Background::Background(Vector *resolution) {
    this->resolution = resolution;
}

void Background::init(unsigned int amount)
{
    Uint32 colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };
    mainColor = 0x333353;

    for(unsigned int i = 0; i < amount; i++) {
        Star star;
        star.color = colors[std::rand() % 4];
        star.pos = Vector(std::rand() % resolution->getIntX(), std::rand() % resolution->getIntY());
        stars.push_back(star);
    }
}

void Background::loop(Context *context, Event *event) {
}

void Background::render(Renderer *renderer, Vector offset) {
    if(renderer) {
        renderer->fill(mainColor);
        Vector localOffset = offset * -0.4;

        for(Star star : stars) {
            int x = star.pos.getIntX() - localOffset.getIntX();
            if(x >= 0) x = x % resolution->getIntX();
            else x = x % resolution->getIntX() + resolution->getIntX();

            int y = star.pos.getIntY() - localOffset.getIntY();
            if(y >= 0) y = y % resolution->getIntY();
            else y = y % resolution->getIntY() + resolution->getIntY();

            renderer->pixel(Vector(x, y), star.color);
        }
    }
}
