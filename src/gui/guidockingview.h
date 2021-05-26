#ifndef GUIDOCKINGVIEW_H
#define GUIDOCKINGVIEW_H

#include <src/gui/base/guisingleelementlistview.h>


class GUIDockingView : public GUISingleElementListView {
public:
    GUIDockingView(const std::string &title);

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::Variant rowModelData(int index) const override;
};

#endif // GUIDOCKINGVIEW_H
