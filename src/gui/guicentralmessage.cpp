#include "guicentralmessage.h"

#include <src/graphics/abstractrenderer.h>

namespace proj172::core {

const unsigned GUICentralMessage::DEFAULT_FLASHING_INTERVAL = 500;

void GUICentralMessage::start(int flashesRemains, unsigned interval) {
    this->flashesRemains = flashesRemains;
    this->flashingTimer = new e172::ElapsedTimer(interval);
    this->flashingTimer->reset();
    this->visible = true;
}

void GUICentralMessage::render(e172::AbstractRenderer *renderer) {
    if(visible) {
        e172::Vector center = renderer->resolution() / 2.0;
        std::string string = title();

        const auto half_size = renderer->drawString(string, center, 0xFFBA73, e172::TextFormat::AlignCenter) / 2;
        renderer->drawRect(center - half_size - e172::Vector<double>(16, 16),
                           center + half_size + e172::Vector<double>(16, 24),
                           0xFFBA73);
    }

    if(flashingTimer && flashingTimer->check()) {
        visible = !visible;
        if(flashesRemains <= 0) {
            flashingTimer = nullptr;
            visible = false;
        }
        flashesRemains--;
    }
}

} // namespace proj172::core
