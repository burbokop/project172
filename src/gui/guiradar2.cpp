#include "guiradar2.h"

#include <src/near.h>
#include <src/engine/objectregistry.h>


Near *GUIRadar2::near() const {
    return m_near;
}

void GUIRadar2::setNear(Near *near) {
    m_near = near;
}

void GUIRadar2::setRowElement(GUIMenuElement *rowElement)
{
    m_rowElement = rowElement;
}

GUIRadar2::GUIRadar2(const std::string &title) : GUIListView(title) {

}

int GUIRadar2::rowCount() const {
    if(m_near) {
        return m_near->entityInFocusCount();
    }
    return 0;
}

std::string GUIRadar2::rowText(int index) const {
    if(m_near) {
        const auto e = m_near->entityInFocus(index);
        if(e == e172::Alive) {
            const auto u = dynamic_cast<e172::Loadable*>(e);
            if(u) {
                return u->loadableId();
            }

            return "id: " + std::to_string(e->entityId());
        }
    }
    return "[error]";
}

GUIMenuElement *GUIRadar2::rowElement(int index) const {
    if(m_rowElement) {

    }

    return m_rowElement;
}
