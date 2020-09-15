#ifndef GUIDOCKINGVIEW_H
#define GUIDOCKINGVIEW_H

#include <src/gui/base/guilistview.h>



class GUIDockingView : public GUIListView {
public:
    GUIDockingView(const std::string &title);

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual GUIMenuElement *rowElement(int) const override;
    virtual e172::Variant rowModelData(int) const override;
};

#endif // GUIDOCKINGVIEW_H
