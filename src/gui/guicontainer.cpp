#include "guicontainer.h"

GUIContainer::GUIContainer(Controller *player) : GUIButton (player) {
}

GUIContainer::GUIContainer(Controller *player, std::string label) : GUIButton (player, label) {
}

GUIContainer::GUIContainer(Controller *player, IInformative *informative) : GUIButton (player, informative) {
}

void GUIContainer::addElement(GUIElement *element){
    elements->push_back(element);

    selected = 0;
    for(GUIElement *element : *elements) {
        GUIButton *button = dynamic_cast<GUIButton*>(element);
        if(button != nullptr) {
            selectedButton = button;
            break;
        }
        selected++;
    }
}

void GUIContainer::update() {
    for(GUIElement *element : *elements) {
        element->update();
    }
}

void GUIContainer::setStack(GUIStack *value)
{
    stack = value;
}

GUIButton *GUIContainer::selectDown() {
    selected++;
    if(selected >= static_cast<int>(elements->size())) {
        selected = minSelectable;
        return dynamic_cast<GUIButton*>(elements->at(static_cast<Uint32>(selected)));
    } else {
        GUIButton* button = dynamic_cast<GUIButton*>(elements->at(static_cast<Uint32>(selected)));
        if(!button) {
            return selectDown();
        } else {
            maxSelectable = selected;
            return button;
        }
    }
}

GUIButton *GUIContainer::selectUp() {
    selected--;
    if(selected < 0) {
        selected = maxSelectable;
        return dynamic_cast<GUIButton*>(elements->at(static_cast<Uint32>(selected)));
    } else {
        GUIButton* button = dynamic_cast<GUIButton*>(elements->at(static_cast<Uint32>(selected)));
        if(!button) {
            return selectUp();
        } else {
            minSelectable = selected;
            return button;
        }
    }
}


void GUIContainer::render(Renderer *renderer, Event *event) {
    if(event->getPressed(81)) {
        selectedButton = selectDown();
    } else if(event->getPressed(82)) {
        selectedButton = selectUp();
    } else if(event->getPressed(40)) {
        if(selectedButton != nullptr) {
            if(selectedButton->press()) {
                stack->push(selectedButton);
            }
        }
    } else if(event->getPressed(SDL_SCANCODE_LEFT)) {
        if(selectedButton != nullptr) {
            selectedButton->dec();
        }
    } else if(event->getPressed(SDL_SCANCODE_RIGHT)) {
        if(selectedButton != nullptr) {
            selectedButton->inc();
        }
    } else if(event->getPressed(SDL_SCANCODE_BACKSPACE)) {
        stack->pop();
    }

    Vector pointer = Vector(margin, margin);
    std::string title = getTitle();
    renderer->string(title, pointer, DEFAULT_COLOR);
    pointer += Vector(0, Renderer::DEFAULT_FONT_SIZE * 2);
    renderer->line(pointer, pointer + Vector(title.size() * static_cast<Uint32>(Renderer::DEFAULT_FONT_SIZE), 0.0), DEFAULT_COLOR);
    pointer += Vector(0, Renderer::DEFAULT_FONT_SIZE);

    int i = 0;
    for(GUIElement *element : *elements) {

        //if(i == selected) renderer->effect(std::bind(anaglyph, std::placeholders::_1, 2, 1));
        if(i == selected) renderer->effect(new Anaglyph(Vector(2, 1)));
        renderer->string(element->getTitle(), pointer, (i == selected) ? SELECTED_COLOR : DEFAULT_COLOR);
        //renderer->string(element->getTitle(), pointer, DEFAULT_COLOR);

        pointer += Vector(4, interval);
        i++;
    }
}

bool GUIContainer::press() {
    return true;
}
