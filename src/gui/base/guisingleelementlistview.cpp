#include "guisingleelementlistview.h"

namespace proj172::core {

void GUISingleElementListView::setRowElement(GUIMenuElement *rowElement) {
    removeChildElement(m_rowElement);
    m_rowElement = rowElement;
    addChildElement(rowElement);
}

e172::ptr<GUIMenuElement> GUISingleElementListView::rowElement(int) const {
    return m_rowElement;
}

} // namespace proj172::core
