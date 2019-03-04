#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include <vector>
#include <functional>


#include "gui/guibutton.h"
#include "gui/guistack.h"



class GUIContainer : public GUIButton {
protected:
    std::vector<GUIElement*> *elements = new std::vector<GUIElement*>();

    GUIButton *selectDown();
    GUIButton *selectUp();

private:

    int interval = 24;
    int selected = -1;

    int minSelectable = 0;
    int maxSelectable = 0;

    GUIButton *selectedButton = nullptr;
    GUIStack *stack = nullptr;





public:
    GUIContainer(Controller *player);
    GUIContainer(Controller *player, std::string label);
    GUIContainer(Controller *player, IInformative *informative);

    void setStack(GUIStack *value);
    void addElement(GUIElement *element);
    void removeElement(GUIElement *element);

    // GUIElement interface
public:
    void update();
    void render(Renderer *renderer, Event *event);

    // GUIButton interface
public:
    bool press();
};

#endif // GUICONTAINER_H