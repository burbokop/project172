#pragma once

#include "base/guimenuelement.h"
#include <e172/time/elapsedtimer.h>

namespace proj172::core {

class GUICentralMessage : public GUIMenuElement {
private:
    static const unsigned DEFAULT_FLASHING_INTERVAL;

    e172::ElapsedTimer *flashingTimer = nullptr;
    bool visible;
    int flashesRemains;

public:
    GUICentralMessage(e172::FactoryMeta &&meta, std::string label)
        : GUIMenuElement(std::move(meta), label)
    {}

    GUICentralMessage(e172::FactoryMeta &&meta, Informative *informative)
        : GUIMenuElement(std::move(meta), informative)
    {}

    void start(int flashesRemains, unsigned interval = DEFAULT_FLASHING_INTERVAL);

    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);
};

} // namespace proj172::core

