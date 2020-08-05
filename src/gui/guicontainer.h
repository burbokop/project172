#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include <vector>
#include <functional>


#include "gui/guimenuelement.h"
#include "gui/guistack.h"


class GUIContainer : public GUIMenuElement {
protected:
    std::vector<GUIMenuElement*> *elements = new std::vector<GUIMenuElement*>();

    GUIMenuElement *selectDown();
    GUIMenuElement *selectUp();

private:

    int interval = 24;
    int selected = -1;

    int minSelectable = 0;
    int maxSelectable = 0;

    GUIMenuElement *selectedElement = nullptr;
    GUIStack *stack = nullptr;


public:
    GUIContainer(Controller *player);
    GUIContainer(Controller *player, std::string label);
    GUIContainer(Controller *player, IInformative *informative);

    void setStack(GUIStack *value);
    void addElement(GUIMenuElement *element);
    void removeElement(GUIMenuElement *element);

    // GUIElement interface
public:
    bool isSelectable();
    bool hasSubElements();

    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUICONTAINER_H
