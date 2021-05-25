#include "guiwareview.h"

#include <src/units/unit.h>

#include <src/capabilities/warestorage.h>
#include <src/capabilities/controller.h>


GUIWareView::GUIWareView(const std::string &title) : GUIListView(title) {}

int GUIWareView::rowCount() const {
    if(controller() && controller()->parentUnit()) {
        if(const auto storage = controller()->parentUnit()->capability<WareStorage>()) {
            return storage->wareInfoCount();
        }
    }
    return 0;
}

std::string GUIWareView::rowText(int index) const {
    if(controller() && controller()->parentUnit()) {
        if(const auto storage = controller()->parentUnit()->capability<WareStorage>()) {
            return storage->wareInfo(index);
        }
    }
    return 0;
}

e172::ptr<GUIMenuElement> GUIWareView::rowElement(int) const {
    return nullptr;
}

e172::Variant GUIWareView::rowModelData(int) const {
    return e172::Variant();
}
