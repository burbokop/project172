#ifndef GUILABEL_H
#define GUILABEL_H


#include "gui/guielement.h"


class GUIMenuElement : public GUIElement {
protected:
    std::string label = "[no data]";
    IInformative *informative = nullptr;
public:
    GUIMenuElement(Controller *player);
    GUIMenuElement(Controller *player, std::string label);
    GUIMenuElement(Controller *player, IInformative *informative);

    virtual std::string getTitle();
    virtual bool isSelectable();
    virtual bool hasSubElements();
    virtual void onEnter();


    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUILABEL_H
