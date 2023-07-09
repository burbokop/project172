#ifndef GUIWAREVIEW_H
#define GUIWAREVIEW_H

#include "base/guisingleelementlistview.h"
#include <functional>

namespace proj172::core {

class Unit;

class GUIWareView : public GUISingleElementListView {
    typedef std::function<e172::ptr<Unit>(const e172::ptr<Controller>&, const e172::Variant &)> UnitProvider;
    static e172::ptr<Unit> provideDefaultUnit(const e172::ptr<Controller>& controller, const e172::Variant &);
    UnitProvider m_unitProvider;
public:
    GUIWareView(e172::FactoryMeta &&meta,
                const std::string &title = std::string(),
                const UnitProvider &unitProvider = provideDefaultUnit)
        : GUISingleElementListView(std::move(meta), title)
        , m_unitProvider(unitProvider)
    {}

    // GUIListView interface
public:
    virtual int rowCount() const override;
    virtual std::string rowText(int index) const override;
    virtual e172::Variant rowModelData(int index) const override;
    UnitProvider unitProvider() const;
    void setUnitProvider(const UnitProvider &unitProvider);
};

} // namespace proj172::core

#endif // GUIWAREVIEW_H
