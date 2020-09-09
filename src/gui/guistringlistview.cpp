#include "guistringlistview.h"

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

GUIMenuElement *GUIStringListView::rowElement(int) const {
    return nullptr;
}
