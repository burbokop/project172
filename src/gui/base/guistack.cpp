#include "guistack.h"
#include "guicontainer.h"
#include "guilistview.h"

#include <src/engine/abstracteventhandler.h>

GUIStack::GUIStack() : GUIElement () {}

void GUIStack::push(GUIElement *element) {
    addChildElement(element);
    if(auto listView = dynamic_cast<GUIListView*>(element))
        listView->setStack(this);

    elements.push_back(element);
}

void GUIStack::pop() {
    if(elements.size() > 0) {
        if(elements.size() == 1) {
            reserved = elements[0];
        }
        removeChildElement(elements.front());
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
