#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include <vector>

#include "guielement.h"
#include "gui/guibutton.h"

class GUIContainer : public GUIElement {
private:
    int interval = 24;
    int selected = -1;

    int minSelectable = 0;
    int maxSelectable = 0;

    GUIButton *selectedButton = nullptr;


    std::vector<GUIElement*> *elements = new std::vector<GUIElement*>();


    GUIButton *selectDown();
    GUIButton *selectUp();


public:
    GUIContainer(Controller *player);
    void addElement(GUIElement *element);

    // GUIElement interface
public:
    std::string getTitle();
    void update();
    void render(Renderer *renderer, Vector *resolution, Event *event);

};

#endif // GUICONTAINER_H
