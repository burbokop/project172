#include "abstractwarecontainer.h"

size_t WareInfo::count() const {
    return m_count;
}

WareInfo::operator std::string() const {
    return m_wareName + " [" + std::to_string(m_count) + "]";
}


WareInfo::WareInfo(const std::string &name, size_t count) {
    m_wareName = name;
    m_count = count;
}

std::string WareInfo::wareName() const {
    return m_wareName;
}


AbstractWareContainer::AbstractWareContainer() {}

size_t AbstractWareContainer::transferWareTo(size_t index, AbstractWareContainer *container, size_t count) {
    if(index < wareInfoCount() && count > 0) {
        const auto wareName = wareInfo(index).wareName();
        count = std::min(capacity() - amount(), count);
        count = removeWare(index, count);
        return container->addWare(wareName, count);
    }
    return 0;
}
