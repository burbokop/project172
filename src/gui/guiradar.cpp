#include "guiradar.h"

#include <src/debug.h>
#include <src/near.h>
#include <src/assettools/loadable.h>

Near *GUIRadar::near() const {
    return m_near;
}

void GUIRadar::setNear(Near *near) {
    m_near = near;
}

GUIRadar::GUIRadar(const std::string &title) : GUISingleElementListView(title) {}

int GUIRadar::rowCount() const {
    if(m_near) {
        return m_near->entityInFocusCount();
    }
    return 0;
}

std::string GUIRadar::rowText(int index) const {
    if(m_near) {
        const auto e = m_near->entityInFocus(index);
        if(e) {
            const auto u = e172::smart_cast<e172::Loadable>(e);
            if(u) {
                const auto lid = u->loadableId();
                if(lid.size() > 0)
                    return lid;

                return "[blank]";
            }

            return "id: " + std::to_string(e->entityId());
        }
    }
    return "[error]";
}

e172::Variant GUIRadar::rowModelData(int index) const {
    if(m_near) {
        const auto e = m_near->entityInFocus(index);
        if(e) {
            return e->entityId();
        }
    }
    return "[error]";
}
