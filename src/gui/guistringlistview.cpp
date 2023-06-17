#include "guistringlistview.h"

namespace proj172::core {

std::vector<std::string> GUIStringListView::data() const {
    return m_data;
}

void GUIStringListView::setData(const std::vector<std::string> &data) {
    m_data = data;
}

int GUIStringListView::rowCount() const {
    return m_data.size();
}

std::string GUIStringListView::rowText(int index) const {
    return m_data[index];
}

e172::ptr<GUIMenuElement> GUIStringListView::rowElement(int) const {
    return nullptr;
}

e172::Variant GUIStringListView::rowModelData(int) const {
    return e172::Variant();
}

} // namespace proj172::core
