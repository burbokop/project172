#pragma once

#include <src/gui/base/guielement.h>
#include <src/utility/ptr.h>

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
    void proceed(e172::Context *context, e172::EventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);

private:
    unsigned m_sizeRelation = 6;
    unsigned m_range = 4098;
    std::list<e172::ptr<e172::Entity>> m_entities;
};

} // namespace proj172::core
