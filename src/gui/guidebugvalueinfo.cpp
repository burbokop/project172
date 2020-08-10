#include "guidebugvalueinfo.h"
#include <math.h>

GUIDebugValueInfo::GUIDebugValueInfo(Controller *player, std::vector<Worker *> *units) {
    m_player = player;
    timer.reset();
}

void GUIDebugValueInfo::tick(Context *context, e172::AbstractEventHandler *eventHandler) {

    if(eventHandler->keyHolded(e172::Scancode1)) {
        coef *= 1.01;
    }
    if(eventHandler->keyHolded(e172::Scancode2)) {
        coef *= 0.99;
    }
}

void GUIDebugValueInfo::render(e172::AbstractRenderer *renderer) {
    auto res = renderer->resolution();

    const double module = std::round(m_player->parent()->getVelocity().module());

    //renderer->applyLensEffect(e172::Vector(20, res.y() - 70), e172::Vector(70, res.y()-20), module / 240.);

    //renderer->applyLensEffect(e172::Vector(), renderer->resolution(), module / 3 + (std::cos(timer.getMilliseconds() / 200.) + 1) * 40);

    //renderer->applySmooth(e172::Vector(00, res.y() - 200), e172::Vector(200, res.y()), coef);

    renderer->drawString(std::to_string(int(module)), e172::Vector(30, res.y() - 55), 0xff8000);
}
