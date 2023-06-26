#pragma once

#include "guimenuelement.h"
#include "guistack.h"

namespace proj172::core {

class GUIListView : public GUIMenuElement {
public:
    GUIListView(e172::FactoryMeta &&meta)
        : GUIMenuElement(std::move(meta))
    {}

    GUIListView(e172::FactoryMeta &&meta, const std::string &title)
        : GUIMenuElement(std::move(meta), title)
    {}

    e172::ptr<GUIStack> stack() const;
    void setStack(const e172::ptr<GUIStack> &stack);
    int verticalInterval() const;
    void setVerticalInterval(int verticalInterval);

    virtual int rowCount() const = 0;
    virtual std::string rowText(int index) const = 0;
    virtual e172::ptr<GUIMenuElement> rowElement(int index) const = 0;
    virtual e172::Variant rowModelData(int index) const = 0;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;

    // GUIMenuElement interface
public:
    virtual bool isSelectable() override;
    virtual bool hasSubElements() override;

private:
    e172::ptr<GUIStack> m_stack = nullptr;
    int m_selectedIndex = 0;
    int m_verticalInterval = 24;
    std::vector<double> m_xOffsets;
    double m_titleXOffset = 0;
};

} // namespace proj172::core
