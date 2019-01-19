#include "guistack.h"
#include "guicontainer.h"

GUIStack::GUIStack() : GUIElement () {}


void GUIStack::push(GUIElement *element) {
    GUIContainer *container = dynamic_cast<GUIContainer*>(element);
    if(container) {
        container->setStack(this);
    }
    elements.push_back(element);
}

void GUIStack::pop() {
    if(elements.size() == 1) {
        reserved = elements[0];
    }
    elements.pop_back();
}

void GUIStack::render(Renderer *renderer, Vector *resolution, Event *event) {
    if(elements.size() > 0) elements[elements.size() - 1]->render(renderer, resolution, event);

    if(event->getPressed(SDL_SCANCODE_RETURN) && reserved) {
        push(reserved);
    }
}

void GUIStack::update() {}

std::string GUIStack::getTitle() { return ""; }
