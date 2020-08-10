#include "guidebugvalueinfo.h"
#include <math.h>

GUIDebugValueInfo::GUIDebugValueInfo(Controller *player, std::vector<Worker *> *units) {
    m_player = player;
}

void GUIDebugValueInfo::tick(Context *context, Event *event) {

    if(event->getKey(SDL_SCANCODE_1)) {
        coef *= 1.01;
    }
    if(event->getKey(SDL_SCANCODE_2)) {
        coef *= 0.99;
    }
}

void GUIDebugValueInfo::render(e172::AbstractRenderer *renderer) {
    auto res = renderer->resolution();

    const double module = std::round(m_player->parent()->getVelocity().module());

    //renderer->applyLensEffect(e172::Vector(20, res.y() - 70), e172::Vector(70, res.y()-20), module / 240.);

    renderer->applyLensEffect(e172::Vector(), renderer->resolution(), module / 120.);

    //renderer->applySmooth(e172::Vector(00, res.y() - 200), e172::Vector(200, res.y()), coef);

    renderer->drawString(std::to_string(int(module)), e172::Vector(30, res.y() - 55), 0xff8000);
}
