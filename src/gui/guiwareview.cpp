#include "guiwareview.h"

#include <src/units/unit.h>

#include <src/capabilities/warestorage.h>

GUIWareView::GUIWareView(const std::string &title) : GUIListView(title) {}

int GUIWareView::rowCount() const {
    if(controller() && controller()->parentUnit()) {
        if(const auto storage = controller()->parentUnit()->capability<WareStorage>()) {
            const auto c = storage->wareInfoCount();

            return c;
        }
    }
    return 0;
}

std::string GUIWareView::rowText(int index) const {
    if(controller() && controller()->parentUnit()) {
        if(const auto storage = controller()->parentUnit()->capability<WareStorage>()) {
            const auto wi = storage->wareInfo(index);

            return wi;
        }
    }
    return 0;
}

GUIMenuElement *GUIWareView::rowElement(int) const {
    return nullptr;
}

e172::Variant GUIWareView::rowModelData(int) const {
    return e172::Variant();
}
