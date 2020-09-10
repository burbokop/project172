#include "guiradar.h"

#include <src/near.h>
#include <src/engine/objectregistry.h>


Near *GUIRadar::near() const {
    return m_near;
}

void GUIRadar::setNear(Near *near) {
    m_near = near;
}

void GUIRadar::setRowElement(GUIMenuElement *rowElement) {
    m_rowElement = rowElement;
}

GUIRadar::GUIRadar(const std::string &title) : GUIListView(title) {}

int GUIRadar::rowCount() const {
    if(m_near) {
        return m_near->entityInFocusCount();
    }
    return 0;
}

std::string GUIRadar::rowText(int index) const {
    if(m_near) {
        const auto e = m_near->entityInFocus(index);
        if(e == e172::Alive) {
            const auto u = dynamic_cast<e172::Loadable*>(e);
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

GUIMenuElement *GUIRadar::rowElement(int index) const {
    if(m_rowElement) {

    }

    return m_rowElement;
}
