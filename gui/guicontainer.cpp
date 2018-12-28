#include "guicontainer.h"

GUIContainer::GUIContainer(Controller *player) : GUIElement (player) {
}



void GUIContainer::addElement(GUIElement *element){
    elements->push_back(element);
    selectDown();
}

std::string GUIContainer::getTitle() {
    return "gogadoda";
}

void GUIContainer::update() {
    for(GUIElement *element : *elements) {
        element->update();
    }
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


void GUIContainer::render(Renderer *renderer, Vector *resolution, Event *event) {
    if(event->getPressed(81)) {
        selectedButton = selectDown();
    } else if(event->getPressed(82)) {
        selectedButton = selectUp();
    } else if(event->getPressed(40)) {
        if(selectedButton != nullptr) {
            selectedButton->press();
        }
    }

    Vector pointer = Vector(margin, margin);
    std::string title = getTitle();
    renderer->string(title, pointer, DEFAULT_COLOR);
    pointer += Vector(0, Renderer::DEFAULT_FONT_SIZE * 2);
    renderer->line(pointer, pointer + Vector(title.size() * static_cast<Uint32>(Renderer::DEFAULT_FONT_SIZE), 0.0), DEFAULT_COLOR);
    pointer += Vector(0, Renderer::DEFAULT_FONT_SIZE);

    int i = 0;
    for(GUIElement *element : *elements) {
        renderer->string(element->getTitle(), pointer, (i == selected) ? SELECTED_COLOR : DEFAULT_COLOR);
        pointer += Vector(4, interval);
        i++;
    }
}
