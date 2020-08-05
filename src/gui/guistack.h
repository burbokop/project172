#ifndef GUISTACK_H
#define GUISTACK_H


#include "gui/guielement.h"


class GUIStack : public GUIElement {
private:
    std::vector<GUIElement*> elements;
    GUIElement* reserved = nullptr;
    GUIElement* current = nullptr;

public:
    GUIStack();

    void push(GUIElement *element);
    void pop();


    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUISTACK_H
