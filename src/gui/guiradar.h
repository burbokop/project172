#pragma once

#include <src/gui/base/guisingleelementlistview.h>

namespace proj172::core {

class Near;

class GUIRadar : public GUISingleElementListView {
public:
    GUIRadar(e172::FactoryMeta &&meta, const std::string &title)
        : GUISingleElementListView(std::move(meta), title)
    {}

    Near *near() { return m_near; }
    const Near *near() const { return m_near; }
    void setNear(Near *near) { m_near = near; }

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::Variant rowModelData(int index) const override;

private:
    Near *m_near = nullptr;
};

} // namespace proj172::core
