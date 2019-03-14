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


    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(Renderer *renderer);
};

#endif // GUILABEL_H
