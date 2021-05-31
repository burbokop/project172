#ifndef GUIMENUELEMENT_H
#define GUIMENUELEMENT_H

#include "guielement.h"

#include <src/iinformative.h>
#include <src/variant.h>

#include <src/graphics/textformat.h>


class GUIMenuElement : public GUIElement {
protected:
    std::string label = "[no data]";
    IInformative *m_informative = nullptr;

    e172::TextFormat m_textFormat = e172::TextFormat::AlignTop | e172::TextFormat::AlignLeft;

    e172::Variant m_modelData;
public:
    GUIMenuElement();
    GUIMenuElement(std::string label);
    GUIMenuElement(IInformative *informative);

    e172::Variant modelData() const;
    void setModelData(const e172::Variant &modelData);

    virtual std::string title();
    virtual bool isSelectable();
    virtual bool hasSubElements();
    virtual void enter(e172::Context *context);

    // Entity interface
public:
    void proceed(e172::Context *, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *);
    e172::TextFormat textFormat() const;
    void setTextFormat(const e172::TextFormat &textFormat);
};

#endif // GUIMENUELEMENT_H
