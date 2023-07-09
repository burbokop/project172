#pragma once

#include "base/guimenuelement.h"
#include <e172/utility/ptr.h>

namespace proj172::core {

class Unit;

class GUIFloatingMessage : public GUIMenuElement {
public:
    GUIFloatingMessage(e172::FactoryMeta &&meta, const e172::ptr<Unit> &parent)
        : GUIMenuElement(std::move(meta), nullptr)
        , m_parent(parent)
    {}

    GUIFloatingMessage(e172::FactoryMeta &&meta, const e172::ptr<Unit> &parent, std::string label)
        : GUIMenuElement(std::move(meta), label)
        , m_parent(parent)
    {}

    GUIFloatingMessage(e172::FactoryMeta &&meta,
                       const e172::ptr<Unit> &parent,
                       Informative *informative)
        : GUIMenuElement(std::move(meta), informative)
        , m_parent(parent)
    {}

    double horisontalOffset() const { return m_horisontalOffset; }

    // GUIElement interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;

protected:
    static const uint32_t DEFAULT_COLOR;
    static const int DEFAULT_FONT_SIZE;
    static const double DEFAULT_FLOATING_SPEED;

    e172::ptr<Unit> m_parent;

private:
    double m_horisontalOffset = 0;
};

} // namespace proj172::core
