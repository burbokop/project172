#ifndef GUIMODULEVIEW_H
#define GUIMODULEVIEW_H

#include "base/guilistview.h"

#include <src/time/elapsedtimer.h>

class GUIModuleView : public GUIListView {

    e172::ElapsedTimer updateTimer = e172::ElapsedTimer(2000);
public:
    GUIModuleView(const std::string &label);

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::ptr<GUIMenuElement> rowElement(int) const override;
    virtual e172::Variant rowModelData(int) const override;
};

#endif // GUIMODULEVIEW_H
