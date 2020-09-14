#include "guibaseelement.h"
#include <algorithm>

GUIBaseElement *GUIBaseElement::parentElement() const {
    return m_parentElement;
}

GUIBaseElement *GUIBaseElement::rootElement() const {
    const auto p = parentElement();
    if(p == nullptr)
        return const_cast<GUIBaseElement*>(this);

    return p->rootElement();
}

Controller *GUIBaseElement::controller() const {
    return m_controller;
}

std::list<GUIBaseElement *> GUIBaseElement::children() const {
    return m_children;
}

void GUIBaseElement::setController(Controller *controller) {
    m_controller = controller;
    for(auto c : m_children) {
        c->setController(controller);
    }
}

GUIBaseElement::GUIBaseElement() {}

bool GUIBaseElement::addChildElement(GUIBaseElement *element) {
    if(element != this && element->m_parentElement == nullptr) {
        const auto it = std::find(m_children.begin(), m_children.end(), element);
        if(it == m_children.end()) {
            m_children.push_back(element);
            element->m_parentElement = this;
            element->m_controller = m_controller;
            return true;
        }
    }
    return false;
}

bool GUIBaseElement::removeChildElement(GUIBaseElement *element) {
    if(element) {
        const auto it = std::find(m_children.begin(), m_children.end(), element);
        if(it != m_children.end()) {
            (*it)->m_parentElement = nullptr;
            (*it)->m_controller = nullptr;
            m_children.erase(it);
            return true;
        }
    }
    return false;
}

void GUIBaseElement::clearChildren() {
    for(auto c : m_children) {
        c->m_parentElement = nullptr;
        c->m_controller = nullptr;
    }
    m_children.clear();
}

void GUIBaseElement::terminateChildren() {
    for(auto c : m_children) {
        delete c;
    }
    m_children.clear();
}
