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

    if(first) {
        lens = renderer->enableLensEffect(e172::Vector(00, res.y() - 200), e172::Vector(200, res.y()), coef / M_PI);
        first = false;
    } else {
        renderer->updateLensEffect(lens, e172::Vector(00, res.y() - 200), e172::Vector(200, res.y()), coef / M_PI);
    }

    const int module = std::round(m_player->parent()->getVelocity().module());

    renderer->drawString(std::to_string(coef), e172::Vector(300, res.y() - 30), 0xff8000);
}
