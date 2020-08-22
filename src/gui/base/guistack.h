#ifndef GUISTACK_H
#define GUISTACK_H

#include "guielement.h"



class GUIStack : public GUIElement {
private:
    std::vector<GUIElement*> elements;
    GUIElement* reserved = nullptr;
    GUIElement* current = nullptr;

public:
    GUIStack();

    void push(GUIElement *element);
    void pop();


    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUISTACK_H
