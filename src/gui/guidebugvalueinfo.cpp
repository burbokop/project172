#include "guidebugvalueinfo.h"

#include "src/abstracteventprovider.h"
#include "src/eventhandler.h"
#include <math.h>
#include <src/capabilities/controller.h>
#include <src/graphics/abstractrenderer.h>
#include <src/units/unit.h>

namespace proj172::core {

void GUIDebugValueInfo::proceed(e172::Context *, e172::EventHandler *eventHandler)
{
    if (eventHandler->keyHolded(e172::Scancode1)) {
        m_coef *= 1.01;
    }
    if(eventHandler->keyHolded(e172::Scancode2)) {
        m_coef *= 0.99;
    }
}

void GUIDebugValueInfo::render(e172::AbstractRenderer *renderer) {
    const auto res = renderer->resolution();
    if(controller()) {
        const double module = std::round(controller()->parentUnit()->velocity().module());
        renderer->drawString(std::to_string(int(module)),
                             e172::Vector<double>(30, res.y() - 55),
                             0xff8000);
    }
}

} // namespace proj172::core
