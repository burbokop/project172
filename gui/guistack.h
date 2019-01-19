#ifndef GUISTACK_H
#define GUISTACK_H

#include "guielement.h"

class GUIStack : public GUIElement {
private:
    std::vector<GUIElement*> elements;
    GUIElement* reserved = nullptr;

public:
    GUIStack();

    void push(GUIElement *element);
    void pop();

    // GUIElement interface
public:
    void render(Renderer *renderer, Vector *resolution, Event *event);
    void update();
    std::string getTitle();
};

#endif // GUISTACK_H
