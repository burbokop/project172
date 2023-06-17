#pragma once

#include "guilistview.h"

namespace proj172::core {

class GUISingleElementListView : public GUIListView {
public:
    GUISingleElementListView(e172::FactoryMeta &&meta)
        : GUIListView(std::move(meta))
    {}

    GUISingleElementListView(e172::FactoryMeta &&meta, const std::string &title)
        : GUIListView(std::move(meta), title)
    {}

    void setRowElement(GUIMenuElement *rowElement);

    // GUIListView interface
public:
    virtual e172::ptr<GUIMenuElement> rowElement(int) const override;

private:
    e172::ptr<GUIMenuElement> m_rowElement = nullptr;
};

} // namespace proj172::core
