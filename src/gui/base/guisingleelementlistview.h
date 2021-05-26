#ifndef GUISINGLEELEMENTLISTVIEW_H
#define GUISINGLEELEMENTLISTVIEW_H

#include "guilistview.h"

class GUISingleElementListView : public GUIListView {
    e172::ptr<GUIMenuElement> m_rowElement = nullptr;
public:
    GUISingleElementListView();
    GUISingleElementListView(const std::string &title);

    void setRowElement(GUIMenuElement *rowElement);

    // GUIListView interface
public:
    virtual e172::ptr<GUIMenuElement> rowElement(int) const override;
};

#endif // GUISINGLEELEMENTLISTVIEW_H
