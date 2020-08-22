#include "guidebugvalueinfo.h"
#include <math.h>
#include <engine/abstracteventhandler.h>
#include <engine/graphics/abstractrenderer.h>

GUIDebugValueInfo::GUIDebugValueInfo(std::list<Entity*> *) {
    timer.reset();
}

void GUIDebugValueInfo::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {

    if(eventHandler->keyHolded(e172::Scancode1)) {
        coef *= 1.01;
    }
    if(eventHandler->keyHolded(e172::Scancode2)) {
        coef *= 0.99;
    }
}

void GUIDebugValueInfo::render(e172::AbstractRenderer *renderer) {
    auto res = renderer->resolution();

    if(controller()) {
        const double module = std::round(controller()->parentUnit()->getVelocity().module());

        //renderer->applyLensEffect(e172::Vector(20, res.y() - 70), e172::Vector(70, res.y()-20), module / 240.);

        //renderer->applyLensEffect(e172::Vector(), renderer->resolution(), module / 3 + (std::cos(timer.getMilliseconds() / 200.) + 1) * 40);

        //renderer->applySmooth(e172::Vector(00, res.y() - 200), e172::Vector(200, res.y()), coef);

        renderer->drawString(std::to_string(int(module)), e172::Vector(30, res.y() - 55), 0xff8000);
    }
}
