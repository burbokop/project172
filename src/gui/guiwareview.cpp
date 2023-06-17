#include "guiwareview.h"

#include <src/units/unit.h>
#include <src/capabilities/warestorage.h>
#include <src/capabilities/controller.h>

namespace proj172::core {

e172::ptr<Unit> GUIWareView::provideDefaultUnit(const e172::ptr<Controller> &controller, const e172::Variant &) {
    return controller->parentUnit();
}

GUIWareView::UnitProvider GUIWareView::unitProvider() const {
    return m_unitProvider;
}

void GUIWareView::setUnitProvider(const UnitProvider &unitProvider) {
    m_unitProvider = unitProvider;
}

int GUIWareView::rowCount() const
{
    if(controller() && m_unitProvider) {
        if(const auto unit = m_unitProvider(controller(), modelData())) {
            if(const auto storage = unit->capability<WareStorage>()) {
                return storage->wareInfoCount();
            }
        }
    }
    return 0;
}

std::string GUIWareView::rowText(int index) const {
    if(controller() && m_unitProvider) {
        if(const auto unit = m_unitProvider(controller(), modelData())) {
            if(const auto storage = unit->capability<WareStorage>()) {
                return storage->wareInfo(index);
            }
        }
    }
    return {};
}

e172::Variant GUIWareView::rowModelData(int index) const {
    if(controller() && m_unitProvider) {
        if(const auto unit = m_unitProvider(controller(), modelData())) {
            if(const auto storage = unit->capability<WareStorage>()) {
                return e172::Variant::fromValue(WareStorage::WareRef(storage, index));
            }
        }
    }
    return e172::Variant();
}

} // namespace proj172::core
