#pragma once

#include "guielement.h"
#include <src/iinformative.h>
#include <src/variant.h>
#include <src/graphics/textformat.h>

namespace proj172::core {

class GUIMenuElement : public GUIElement {
public:
    GUIMenuElement(e172::FactoryMeta &&meta)
        : GUIElement(std::move(meta))
    {}

    GUIMenuElement(e172::FactoryMeta &&meta, std::string label)
        : GUIElement(std::move(meta))
        , m_label(label)
    {}

    GUIMenuElement(e172::FactoryMeta &&meta, IInformative *informative)
        : GUIElement(std::move(meta))
        , m_informative(informative)
    {}

    e172::Variant modelData() const;
    void setModelData(const e172::Variant &modelData);
    e172::TextFormat textFormat() const;
    void setTextFormat(const e172::TextFormat &textFormat);

    virtual std::string title();
    virtual bool isSelectable() { return false; }
    virtual bool hasSubElements() { return false; }
    virtual void enter(e172::Context *context);

    // Entity interface
public:
    void proceed(e172::Context *, e172::EventHandler *);
    void render(e172::AbstractRenderer *);

protected:
    std::string m_label = "[no data]";
    IInformative *m_informative = nullptr;
    e172::TextFormat m_textFormat = e172::TextFormat::AlignTop | e172::TextFormat::AlignLeft;
    e172::Variant m_modelData;
};

} // namespace proj172::core
