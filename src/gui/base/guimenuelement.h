#ifndef GUILABEL_H
#define GUILABEL_H

#include "guielement.h"




class GUIMenuElement : public GUIElement {
protected:
    std::string label = "[no data]";
    IInformative *informative = nullptr;
public:
    GUIMenuElement();
    GUIMenuElement(std::string label);
    GUIMenuElement(IInformative *informative);

    virtual std::string getTitle();
    virtual bool isSelectable();
    virtual bool hasSubElements();
    virtual void onEnter();

    // Entity interface
public:
    void proceed(e172::Context *, e172::AbstractEventHandler *);
    void render(e172::AbstractRenderer *);
};

#endif // GUILABEL_H
