#include "guisingleelementlistview.h"

GUISingleElementListView::GUISingleElementListView() {}

GUISingleElementListView::GUISingleElementListView(const std::string &title) : GUIListView(title) {}

void GUISingleElementListView::setRowElement(GUIMenuElement *rowElement) {
    removeChildElement(m_rowElement);
    m_rowElement = rowElement;
    addChildElement(rowElement);
}

e172::ptr<GUIMenuElement> GUISingleElementListView::rowElement(int) const {
    return m_rowElement;
}
