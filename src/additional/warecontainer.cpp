#include "warecontainer.h"


size_t WareContainer::amount() const {
    size_t sum = 0;
    for(auto s : m_data) {
        sum += s.second;
    }
    return sum;
}

size_t WareContainer::addWare(std::string ware, size_t count) {
    if(count > 0) {
        count = std::min(m_capacity - amount(), count);

        bool found = false;
        for(size_t i = 0; i < m_data.size(); ++i) {
            if(m_data[i].first == ware) {
                m_data[i].second += count;
                found = true;
                break;
            }
        }

        if(!found) {
            m_data.push_back({ ware, count });
        }

        return count;
    }
    return 0;
}

size_t WareContainer::removeWare(size_t index, size_t count) {
    auto& w = m_data[index];
    count = std::min(w.second, count);
    w.second -= count;

    if(w.second == 0)
        m_data.erase(m_data.begin() + index);

    return count;
}

size_t WareContainer::transferWareTo(size_t index, WareContainer *container, size_t count) {
    if(index < wareInfoCount() && count > 0) {
        const auto wareName = wareInfo(index).wareName();
        count = std::min(m_capacity - amount(), count);
        count = removeWare(index, count);
        return container->addWare(wareName, count);
    }
    return 0;
}


WareContainer::WareContainer(size_t capacity) {
    m_capacity = capacity;
}

size_t WareContainer::wareInfoCount() const {
    return m_data.size();
}

WareInfo WareContainer::wareInfo(size_t index) const {
    return WareInfo(m_data[index].first, m_data[index].second);
}

size_t WareInfo::count() const {
    return m_count;
}

WareInfo::WareInfo(const std::string &name, size_t count) {
    m_wareName = name;
    m_count = count;
}

std::string WareInfo::wareName() const {
    return m_wareName;
}

size_t WareContainer::capacity() const {
    return m_capacity;
}

void WareContainer::setCapacity(const size_t &capacity) {
    m_capacity = capacity;
}
