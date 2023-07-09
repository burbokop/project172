#pragma once

#include "base/guilistview.h"
#include <e172/time/elapsedtimer.h>

namespace proj172::core {

class GUIModuleView : public GUIListView {
public:
    GUIModuleView(e172::FactoryMeta &&meta, const std::string &label)
        : GUIListView(std::move(meta), label)
    {}

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::ptr<GUIMenuElement> rowElement(int) const override;
    virtual e172::Variant rowModelData(int) const override;

private:
    e172::ElapsedTimer m_updateTimer = e172::ElapsedTimer(2000);
};

} // namespace proj172::core
