#pragma once

#include "base/guimenuelement.h"
#include <functional>

namespace proj172::core {

class GUISwitch : public GUIMenuElement {

public:
    GUISwitch(e172::FactoryMeta &&meta,
              std::function<void()> on = nullptr,
              std::function<void()> off = nullptr)
        : GUIMenuElement(std::move(meta))
        , m_on(on)
        , m_off(off)
    {}

    GUISwitch(e172::FactoryMeta &&meta,
              const std::string &label,
              std::function<void()> on = nullptr,
              std::function<void()> off = nullptr)
        : GUIMenuElement(std::move(meta), label)
        , m_on(on)
        , m_off(off)
    {}

    GUISwitch(e172::FactoryMeta &&meta,
              Informative *informative,
              std::function<void()> on = nullptr,
              std::function<void()> off = nullptr)
        : GUIMenuElement(std::move(meta), informative)
        , m_on(on)
        , m_off(off)
    {}

    // GUILabel interface
public:
    bool isSelectable() override { return true; }
    void enter(e172::Context *) override;

private:
    std::function<void()> m_on;
    std::function<void()> m_off;
    bool m_enabled = false;
};

} // namespace proj172::core
