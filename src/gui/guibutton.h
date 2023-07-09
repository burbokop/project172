#pragma once

#include "base/guimenuelement.h"
#include <functional>

namespace proj172::core {

class GUIButton : public GUIMenuElement {
public:
    using F0 = std::function<void(const e172::Variant &)>;
    using F1 = std::function<void(const e172::ptr<Controller> &, const e172::Variant &)>;
    using F2
        = std::function<void(e172::Context *, const e172::ptr<Controller> &, const e172::Variant &)>;

    GUIButton(e172::FactoryMeta &&meta, const std::string &title, const F0 &f)
        : GUIMenuElement(std::move(meta), title)
        , m_f0(f)
    {}

    GUIButton(e172::FactoryMeta &&meta, const std::string &title, const F1 &f)
        : GUIMenuElement(std::move(meta), title)
        , m_f1(f)
    {}

    GUIButton(e172::FactoryMeta &&meta, const std::string &title, const F2 &f)
        : GUIMenuElement(std::move(meta), title)
        , m_f2(f)
    {}

    // GUIMenuElement interface
public:
    virtual bool isSelectable() override;
    virtual void enter(e172::Context *context) override;

private:
    F0 m_f0;
    F1 m_f1;
    F2 m_f2;
};

} // namespace proj172::core
