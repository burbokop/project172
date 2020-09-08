#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include "guimenuelement.h"
#include "guistack.h"

#include <vector>
#include <functional>


class GUIContainer : public GUIMenuElement {
protected:

    GUIMenuElement *selectDown();
    GUIMenuElement *selectUp();

private:
    std::vector<GUIMenuElement*> m_menuElements;

    int interval = 24;
    int selected = -1;

    int minSelectable = 0;
    int maxSelectable = 0;

    GUIMenuElement *selectedElement = nullptr;
    GUIStack *stack = nullptr;


public:
    GUIContainer();
    GUIContainer(std::string label);
    GUIContainer(IInformative *informative);

    void setStack(GUIStack *value);
    void addMenuElement(GUIMenuElement *element);
    void removeMenuElement(GUIMenuElement *element);
    void clearElements();
    void terminateElements();

    // GUIElement interface
public:
    bool isSelectable();
    bool hasSubElements();

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUICONTAINER_H
