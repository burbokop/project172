#include "guicontainer.h"

#include <sdlimplementation/sdlrenderer.h>



GUIContainer::GUIContainer(Controller *player) : GUIMenuElement (player) {
}

GUIContainer::GUIContainer(Controller *player, std::string label) : GUIMenuElement (player, label) {
}

GUIContainer::GUIContainer(Controller *player, IInformative *informative) : GUIMenuElement (player, informative) {
}

void GUIContainer::addElement(GUIMenuElement *element){
    elements->push_back(element);

    selected = 0;
    for(GUIMenuElement *element : *elements) {
        if(element->isSelectable()) {
            selectedElement = element;
            break;
        }
        selected++;
    }
}

void GUIContainer::removeElement(GUIMenuElement *element) {
    std::vector<GUIMenuElement*>::iterator it = std::find(elements->begin(), elements->end(), element);
    if(it != elements->end()) {
        elements->erase(it);
    }
}


void GUIContainer::setStack(GUIStack *value) {
    stack = value;
}


GUIMenuElement *GUIContainer::selectDown() {
    if(elements->size() > 0) {
        selected++;
        if(selected >= static_cast<int>(elements->size())) {
            selected = minSelectable;
            unsigned long i = static_cast<unsigned long>(selected);
            if(i < elements->size()) {
                return elements->at(i);
            }
            return selectUp();
        } else {
            unsigned long i = static_cast<unsigned long>(selected);
            if(i < elements->size()) {
                GUIMenuElement *element = elements->at(i);
                if(element->isSelectable()) {
                    maxSelectable = selected;
                    return element;
                } else {
                    return selectDown();
                }
            }
            return selectUp();
        }
    }
    return nullptr;
}

GUIMenuElement *GUIContainer::selectUp() {
    if(elements->size() > 0) {
        selected--;
        if(selected < 0) {
            selected = maxSelectable;
            unsigned long i = static_cast<unsigned long>(selected);
            if(i < elements->size()) {
                return elements->at(i);
            }
            return selectUp();
        } else {
            unsigned long i = static_cast<unsigned long>(selected);
            if(i < elements->size()) {
                GUIMenuElement *element = elements->at(i);
                if(element->isSelectable()) {
                    minSelectable = selected;
                    return element;
                } else {
                    return selectUp();
                }
            }
            return selectUp();
        }
    }
    return nullptr;
}


bool GUIContainer::isSelectable() {
    return true;
}

bool GUIContainer::hasSubElements() {
    return true;
}

void GUIContainer::tick(Context *context, Event *event) {
    UNUSED(context);
    if(event->getPressed(SDL_SCANCODE_DOWN)) {
        selectedElement = selectDown();
    } else if(event->getPressed(SDL_SCANCODE_UP)) {
        selectedElement = selectUp();
    } else if(event->getPressed(SDL_SCANCODE_RETURN)) {
        if(selectedElement != nullptr) {
            selectedElement->onEnter();
            if(selectedElement->hasSubElements()) {
                stack->push(selectedElement);
            }
        }
    } else if(event->getPressed(SDL_SCANCODE_BACKSPACE)) {
        stack->pop();
    }
}


void GUIContainer::render(e172::AbstractRenderer *renderer) {
    if(elements) {
        e172::Vector pointer = e172::Vector(margin, margin);
        std::string title = getTitle();
        renderer->drawString(title, pointer, DEFAULT_COLOR);
        pointer += e172::Vector(0, SDLRenderer::DEFAULT_FONT_SIZE * 2);
        renderer->drawLine(pointer, pointer + e172::Vector(title.size() * static_cast<Uint32>(SDLRenderer::DEFAULT_FONT_SIZE), 0.0), DEFAULT_COLOR);
        pointer += e172::Vector(0, SDLRenderer::DEFAULT_FONT_SIZE);

        int i = 0;
        for(GUIMenuElement *element : *elements) {
            if(element) {
                if(i == selected)
                    renderer->enableEffect(0);

                renderer->drawString(element->getTitle(), pointer, (i == selected) ? SELECTED_COLOR : DEFAULT_COLOR);
                renderer->disableEffect(0);
                pointer += e172::Vector(4, interval);
                i++;
            }
        }
    }
}
