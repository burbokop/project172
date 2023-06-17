#ifndef GUISWITCH_H
#define GUISWITCH_H

#include <functional>

#include <src/gui/base/guimenuelement.h>

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
              IInformative *informative,
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

#endif // GUISWITCH_H
