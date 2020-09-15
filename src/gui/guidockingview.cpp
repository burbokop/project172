#include "guidockingview.h"

#include <src/units/unit.h>
#include <src/capabilities/docker.h>

GUIDockingView::GUIDockingView(const std::string &title) : GUIListView(title) {}

int GUIDockingView::rowCount() const {
    if(controller()) {
        if(const auto pu = controller()->parentUnit()) {
            if(const auto docker = pu->docker()) {
                return docker->sessionCount();
            }
        }
    }
    return 0;
}

std::string GUIDockingView::rowText(int index) const {
    if(controller()) {
        if(const auto pu = controller()->parentUnit()) {
            if(const auto docker = pu->docker()) {
                return docker->sessionInfo(index);
            }
        }
    }
    return "[error]";
}

GUIMenuElement *GUIDockingView::rowElement(int) const {
    return nullptr;
}

e172::Variant GUIDockingView::rowModelData(int) const {
    return e172::Variant();
}
