#pragma once

#include "base/guielement.h"
#include <e172/utility/ptr.h>

namespace e172 {
class Entity;
}

namespace proj172::core {

class GUIMiniMap : public GUIElement {
public:
    GUIMiniMap(e172::FactoryMeta &&meta)
        : GUIElement(std::move(meta))
    {}

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    void render(e172::Context *context, e172::AbstractRenderer *renderer) override;

private:
    unsigned m_sizeRelation = 6;
    unsigned m_range = 4098;
};

} // namespace proj172::core
