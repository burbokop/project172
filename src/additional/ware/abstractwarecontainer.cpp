#include "abstractwarecontainer.h"


size_t WareInfo::count() const {
    return m_count;
}

WareInfo::operator std::string() const {
    return m_isValid ? (m_wareName + " [" + std::to_string(m_count) + "]") : "invalid";
}

bool WareInfo::isValid() const {
    return m_isValid;
}

WareInfo::WareInfo(const std::string &name, size_t count, bool isValid) {
    m_wareName = name;
    m_count = count;
    m_isValid = isValid;
}

std::string WareInfo::wareName() const {
    return m_wareName;
}

AbstractWareContainer::AbstractWareContainer() {}

size_t AbstractWareContainer::transferWareTo(size_t index, const e172::ptr<AbstractWareContainer> &container, size_t count) {
    if(index < wareInfoCount() && count > 0) {
        const auto wareName = wareInfo(index).wareName();
        count = std::min(capacity() - amount(), count);
        count = wareAwailableRemovingAmount(index, count);
        count = container->addWare(wareName, count);
        return removeWare(index, count);
    }
    return 0;
}

std::ostream &operator<<(std::ostream &stream, const WareInfo &info) {
    return stream << info.wareName() << " [" << info.count() << "]";
}
