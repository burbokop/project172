#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include <vector>

#include "guielement.h"
#include "gui/guibutton.h"
#include "guistack.h"

class GUIContainer : public GUIButton {
private:
    int interval = 24;
    int selected = -1;

    int minSelectable = 0;
    int maxSelectable = 0;

    GUIButton *selectedButton = nullptr;
    GUIStack *stack = nullptr;

    std::vector<GUIElement*> *elements = new std::vector<GUIElement*>();


    GUIButton *selectDown();
    GUIButton *selectUp();


public:
    GUIContainer(Controller *player);
    GUIContainer(Controller *player, std::string label);
    GUIContainer(Controller *player, IInformative *informative);

    void setStack(GUIStack *value);
    void addElement(GUIElement *element);

    // GUIElement interface
public:
    void update();
    void render(Renderer *renderer, Vector *resolution, Event *event);

    // GUIButton interface
public:
    bool press();
};

#endif // GUICONTAINER_H
