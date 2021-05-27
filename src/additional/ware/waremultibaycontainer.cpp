#include "waremultibaycontainer.h"


WareMultiBayContainer::WareMultiBayContainer(const std::vector<WareContainer> &data) {
    m_data = data;
}

void WareMultiBayContainer::setBayCount(size_t count) {
    if(count > 0) {
        if(count > size()) {
            for(size_t i = 0, c = count - size(); i < c; ++i) {
                m_data.push_back(WareContainer());
            }
        } else if(count < size()) {
            m_data.resize(count);
        }
    }
}

size_t WareMultiBayContainer::wareAwailableAdditingAmount(std::string ware, size_t count, bool ignoreAllowed) {
    for(auto& d : m_data) {
        if(d.isInputAllowed(ware)) {
            size_t c = d.wareAwailableAdditingAmount(ware, count, ignoreAllowed);
            if(c > 0)
                return c;
        }
    }
    return 0;
}

size_t WareMultiBayContainer::wareAwailableRemovingAmount(size_t index, size_t count, bool ignoreAllowed) {
    size_t ci = 0;
    for(size_t i = 0; i < m_data.size(); ++i) {
        const auto wareInfoCount = m_data[i].wareInfoCount();
        for(size_t j = 0; j < wareInfoCount; ++j) {
            if(ci == index) {
                return m_data[i].wareAwailableRemovingAmount(j, count, ignoreAllowed);
            }
            ++ci;
        }
    }
    return 0;
}

size_t WareMultiBayContainer::addWare(std::string ware, size_t count, bool ignoreAllowed) {
    for(auto& d : m_data) {
        if(d.isInputAllowed(ware)) {
            const auto c = d.addWare(ware, count, ignoreAllowed);
            if(c > 0)
                return c;
        }
    }
    return 0;
}

size_t WareMultiBayContainer::removeWare(size_t index, size_t count, bool ignoreAllowed) {
    size_t ci = 0;
    for(size_t i = 0; i < m_data.size(); ++i) {
        const auto wareInfoCount = m_data[i].wareInfoCount();
        for(size_t j = 0; j < wareInfoCount; ++j) {
            if(ci == index) {
                return m_data[i].removeWare(j, count, ignoreAllowed);
            }
            ++ci;
        }
    }
    return 0;
}

size_t WareMultiBayContainer::wareInfoCount() const {
    size_t result = 0;
    for(auto d : m_data) {
        result += d.wareInfoCount();
    }
    return result;
}

WareInfo WareMultiBayContainer::wareInfo(size_t index) const {
    size_t ci = 0;
    for(size_t i = 0; i < m_data.size(); ++i) {
        const auto wareInfoCount = m_data[i].wareInfoCount();
        for(size_t j = 0; j < wareInfoCount; ++j) {
            if(ci == index) {
                return m_data[i].wareInfo(j);
            }
            ++ci;
        }
    }
    return WareInfo("", 0);
}

size_t WareMultiBayContainer::amount() const {
    size_t result = 0;
    for(auto d : m_data) {
        result += d.amount();
    }
    return result;
}

size_t WareMultiBayContainer::capacity() const {
    size_t result = 0;
    for(auto d : m_data) {
        result += d.capacity();
    }
    return result;
}
