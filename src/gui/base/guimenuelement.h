#ifndef GUILABEL_H
#define GUILABEL_H

#include "guielement.h"




class GUIMenuElement : public GUIElement {
protected:
    std::string label = "[no data]";
    IInformative *informative = nullptr;

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
    virtual void enter();

    // Entity interface
public:
    void proceed(e172::Context *, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *);
};

#endif // GUILABEL_H
