#include "guidockingview.h"

#include "../capabilities/controller.h"
#include "../capabilities/docker.h"
#include "../units/unit.h"

namespace proj172::core {

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

} // namespace proj172::core
