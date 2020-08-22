#include "guicontainer.h"

#include <sdlimplementation/sdlrenderer.h>

#include <engine/abstracteventhandler.h>



GUIContainer::GUIContainer(std::string label) : GUIMenuElement (label) {}

GUIContainer::GUIContainer(IInformative *informative) : GUIMenuElement (informative) {}

void GUIContainer::addMenuElement(GUIMenuElement *element){
    if(addChildElement(element)) {
        m_menuElements.push_back(element);

        selected = 0;
        for(GUIMenuElement *element : m_menuElements) {
            if(element->isSelectable()) {
                selectedElement = element;
                break;
            }
            selected++;
        }
    }
}

void GUIContainer::removeMenuElement(GUIMenuElement *element) {
    if(removeChildElement(element)) {
        const auto it = std::find(m_menuElements.begin(), m_menuElements.end(), element);
        if(it != m_menuElements.end()) {
            m_menuElements.erase(it);
        }
    }
}

void GUIContainer::clearElements() {
    clearChildren();
    m_menuElements.clear();
}

void GUIContainer::setStack(GUIStack *value) {
    stack = value;
}


GUIMenuElement *GUIContainer::selectDown() {
    if(m_menuElements.size() > 0) {
        selected++;
        if(selected >= static_cast<int>(m_menuElements.size())) {
            selected = minSelectable;
            unsigned long i = static_cast<unsigned long>(selected);
            if(i < m_menuElements.size()) {
                return m_menuElements.at(i);
            }
            return selectUp();
        } else {
            unsigned long i = static_cast<unsigned long>(selected);
            if(i < m_menuElements.size()) {
                GUIMenuElement *element = m_menuElements.at(i);
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
    if(m_menuElements.size() > 0) {
        selected--;
        if(selected < 0) {
            selected = maxSelectable;
            unsigned long i = static_cast<unsigned long>(selected);
            if(i < m_menuElements.size()) {
                return m_menuElements.at(i);
            }
            return selectUp();
        } else {
            unsigned long i = static_cast<unsigned long>(selected);
            if(i < m_menuElements.size()) {
                GUIMenuElement *element = m_menuElements.at(i);
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

GUIContainer::GUIContainer() {}


bool GUIContainer::isSelectable() {
    return true;
}

bool GUIContainer::hasSubElements() {
    return true;
}

void GUIContainer::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    UNUSED(context);
    if(eventHandler->keySinglePressed(e172::ScancodeDown)) {
        selectedElement = selectDown();
    } else if(eventHandler->keySinglePressed(e172::ScancodeUp)) {
        selectedElement = selectUp();
    } else if(eventHandler->keySinglePressed(e172::ScancodeReturn)) {
        if(selectedElement != nullptr) {
            selectedElement->onEnter();
            if(selectedElement->hasSubElements()) {
                stack->push(selectedElement);
            }
        }
    } else if(eventHandler->keySinglePressed(e172::ScancodeBackSpace)) {
        stack->pop();
    }
}


void GUIContainer::render(e172::AbstractRenderer *renderer) {
    e172::Vector pointer = e172::Vector(margin(), margin());
    std::string title = getTitle();
    renderer->drawString(title, pointer, DefaultColor);
    pointer += e172::Vector(0, SDLRenderer::DefaultFontSize * 2);
    renderer->drawLine(pointer, pointer + e172::Vector(title.size() * static_cast<uint32_t>(SDLRenderer::DefaultFontSize), 0.0), DefaultColor);
    pointer += e172::Vector(0, SDLRenderer::DefaultFontSize);

    int i = 0;
    for(GUIMenuElement *element : m_menuElements) {
        if(element) {
            if(i == selected)
                renderer->enableEffect(0);

            renderer->drawString(element->getTitle(), pointer, (i == selected) ? SelectedColor : DefaultColor);
            renderer->disableEffect(0);
            pointer += e172::Vector(4, interval);
            i++;
        }
    }
}
