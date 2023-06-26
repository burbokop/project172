#pragma once

#include <src/gui/guifloatingmessage.h>

namespace proj172::core {

class GUIBlushingFloatingMessage : public GUIFloatingMessage {
public:
    GUIBlushingFloatingMessage(e172::FactoryMeta &&meta, const e172::ptr<Unit> &parent)
        : GUIFloatingMessage(std::move(meta), parent)
    {}

    GUIBlushingFloatingMessage(e172::FactoryMeta &&meta,
                               const e172::ptr<Unit> &parent,
                               std::uint32_t value)
        : GUIFloatingMessage(std::move(meta), parent, std::to_string(value))
        , m_value(value)
    {}

    GUIBlushingFloatingMessage(e172::FactoryMeta &&meta,
                               const e172::ptr<Unit> &parent,
                               Informative *informative)
        : GUIFloatingMessage(std::move(meta), parent, informative)
    {}

    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);

private:
    std::uint32_t m_value = 0;
};

} // namespace proj172::core
