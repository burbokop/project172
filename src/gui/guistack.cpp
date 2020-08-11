#include "guistack.h"
#include "guicontainer.h"

#include <engine/abstracteventhandler.h>

GUIStack::GUIStack() : GUIElement () {}

void GUIStack::push(GUIElement *element) {
    GUIContainer *container = dynamic_cast<GUIContainer*>(element);
    if(container) {
        container->setStack(this);
    }
    elements.push_back(element);
}

void GUIStack::pop() {
    if(elements.size() > 0) {
        if(elements.size() == 1) {
            reserved = elements[0];
        }
        elements.pop_back();
    }
}

void GUIStack::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(context);
    if(elements.size() > 0) {
        current = elements[elements.size() - 1];
    } else {
        current = nullptr;
        if(eventHandler->keySinglePressed(e172::ScancodeReturn) && reserved) {
            push(reserved);
        }
    }

    if(current) {
        current->proceed(context, eventHandler);
    }
}

void GUIStack::render(e172::AbstractRenderer *renderer) {
    if(current) {
        current->render(renderer);
    }
}
