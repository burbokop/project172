#include "guimenu.h"

GUIMenu::GUIMenu(std::string label) : GUIListView(label) {}

void GUIMenu::addMenuElement(const e172::ptr<GUIMenuElement> &element){
    if(addChildElement(element)) {
        m_menuElements.push_back(element);
    }
}

void GUIMenu::removeMenuElement(const e172::ptr<GUIMenuElement> &element) {
    if(removeChildElement(element)) {
        const auto it = std::find(m_menuElements.begin(), m_menuElements.end(), element);
        if(it != m_menuElements.end()) {
            m_menuElements.erase(it);
        }
    }
}

void GUIMenu::clearElements() {
    clearChildren();
    m_menuElements.clear();
}

void GUIMenu::terminateElements() {
    terminateChildren();
    m_menuElements.clear();
}

e172::ptr<GUIMenu> GUIMenu::withMenuChildren(const std::list<e172::ptr<GUIMenuElement> > &children) {
    for(const auto& c : children) {
        if(c)
            addMenuElement(c);
    }
    return this;
}

int GUIMenu::rowCount() const {
    return m_menuElements.size();
}

std::string GUIMenu::rowText(int index) const {
    if(const auto e = m_menuElements[index]) {
        return e->title();
    }
    return "[error]";
}

e172::ptr<GUIMenuElement> GUIMenu::rowElement(int index) const {
    return m_menuElements[index];
}

e172::Variant GUIMenu::rowModelData(int) const {
    return e172::Variant();
}
