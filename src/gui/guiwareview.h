#ifndef GUIWAREVIEW_H
#define GUIWAREVIEW_H

#include <src/gui/base/guilistview.h>



class GUIWareView : public GUIListView {
public:
    GUIWareView(const std::string &title = std::string());

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual GUIMenuElement *rowElement(int) const override;
    virtual e172::Variant rowModelData(int) const override;
};

#endif // GUIWAREVIEW_H
