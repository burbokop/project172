#include "guielement.h"

#include <algorithm>

namespace proj172::core {

e172::ptr<GUIElement> GUIElement::rootElement() const
{
    const auto p = parentElement();
    if(!p)
        return const_cast<GUIElement*>(this);

    return p->rootElement();
}

void GUIElement::setController(const e172::ptr<Controller> &controller)
{
    m_controller = controller;
    for(auto c : m_children) {
        c->setController(controller);
    }
}

void GUIElement::setInFocus(bool inFocus)
{
    m_inFocus = inFocus;
    setKeyboardEnabled(inFocus);
    for(auto c : m_children) {
        c->setInFocus(inFocus);
    }
}

e172::ptr<GUIElement> GUIElement::withChildren(const std::list<e172::ptr<GUIElement>> &children) {
    for(const auto& c : children) {
        if(c)
            addChildElement(c);
    }
    return this;
}

GUIElement::GUIElement(e172::FactoryMeta &&meta)
    : e172::Entity(std::move(meta))
{
    setDepth(100);
}

bool GUIElement::addChildElement(const e172::ptr<GUIElement> &element)
{
    if (element != this && !element->m_parentElement) {
        const auto it = std::find(m_children.begin(), m_children.end(), element);
        if (it == m_children.end()) {
            m_children.push_back(element);
            element->m_parentElement = this;
            element->m_controller = m_controller;
            return true;
        }
    }
    return false;
}

bool GUIElement::removeChildElement(const e172::ptr<GUIElement> &element) {
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

void GUIElement::clearChildren() {
    for(auto c : m_children) {
        c->m_parentElement = nullptr;
        c->m_controller = nullptr;
    }
    m_children.clear();
}

void GUIElement::terminateChildren() {
    for (const auto &c : m_children) {
        c.destroy();
    }
    m_children.clear();
}

} // namespace proj172::core
