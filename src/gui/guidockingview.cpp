#include "guidockingview.h"

#include <src/units/unit.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/controller.h>

GUIDockingView::GUIDockingView(const std::string &title) : GUISingleElementListView(title) {}

int GUIDockingView::rowCount() const {
    if(controller()) {
        if(const auto pu = controller()->parentUnit()) {
            if(const auto docker = pu->capability<Docker>()) {
                return docker->sessionCount();
            }
        }
    }
    return 0;
}

std::string GUIDockingView::rowText(int index) const {
    if(controller()) {
        if(const auto pu = controller()->parentUnit()) {
            if(const auto docker = pu->capability<Docker>()) {
                return docker->sessionInfo(index);
            }
        }
    }
    return "[error]";
}

e172::Variant GUIDockingView::rowModelData(int index) const {
    return index;
}
