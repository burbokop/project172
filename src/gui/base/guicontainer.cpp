#include "guicontainer.h"

GUIContainer::GUIContainer(std::string label) : GUIListView(label) {}

void GUIContainer::addMenuElement(GUIMenuElement *element){
    if(addChildElement(element)) {
        m_menuElements.push_back(element);
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

void GUIContainer::terminateElements() {
    terminateChildren();
    m_menuElements.clear();
}

int GUIContainer::rowCount() const {
    return m_menuElements.size();
}

std::string GUIContainer::rowText(int index) const {
    if(const auto e = m_menuElements[index]) {
        return e->title();
    }
    return "[error]";
}

GUIMenuElement *GUIContainer::rowElement(int index) const {
    return m_menuElements[index];
}

e172::Variant GUIContainer::rowModelData(int) const {
    return e172::Variant();
}
