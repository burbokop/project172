#pragma once

#include <src/gui/base/guisingleelementlistview.h>

namespace proj172::core {

class GUIDockingView : public GUISingleElementListView {
public:
    GUIDockingView(e172::FactoryMeta &&meta, const std::string &title)
        : GUISingleElementListView(std::move(meta), title)
    {}

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::Variant rowModelData(int index) const override;
};

} // namespace proj172::core
