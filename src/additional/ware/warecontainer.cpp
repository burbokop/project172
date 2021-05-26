#include "warecontainer.h"

#include <algorithm>

size_t WareContainer::amount() const {
    size_t sum = 0;
    for(auto s : m_data) {
        sum += s.second;
    }
    return sum;
}

bool WareContainer::containsAllowedInput(const std::string &wareName) const {
    if(std::get_if<all_allowed_t>(&m_allowedInput)) {
        return true;
    } else {
        if(const auto ptr = std::get_if<std::vector<std::string>>(&m_allowedInput)) {
            return std::find(ptr->begin(), ptr->end(), wareName) != ptr->end();
        }
    }
    return false;
}

bool WareContainer::containsAllowedOutput(const std::string &wareName) const {
    if(std::get_if<all_allowed_t>(&m_allowedOutput)) {
        return true;
    } else {
        if(const auto ptr = std::get_if<std::vector<std::string>>(&m_allowedOutput)) {
            return std::find(ptr->begin(), ptr->end(), wareName) != ptr->end();
        }
    }
    return false;
}

WareContainer::Allowed WareContainer::allowedInput() const {
    return m_allowedInput;
}

void WareContainer::setAllowedInput(const Allowed &allowedInput) {
    m_allowedInput = allowedInput;
}

WareContainer::Allowed WareContainer::allowedOutput() const {
    return m_allowedOutput;
}

void WareContainer::setAllowedOutput(const Allowed &allowedOutput) {
    m_allowedOutput = allowedOutput;
}

bool WareContainer::isAllInputAllowed() const {
    return std::get_if<all_allowed_t>(&m_allowedInput);
}

bool WareContainer::isAllOutputAllowed() const {
    return std::get_if<all_allowed_t>(&m_allowedOutput);
}

bool WareContainer::isNoInputAllowed() const {
    if(const auto ptr = std::get_if<std::vector<std::string>>(&m_allowedInput)) {
        return ptr->size() == 0;
    }
    return false;
}

bool WareContainer::isNoOutputAllowed() const {
    if(const auto ptr = std::get_if<std::vector<std::string>>(&m_allowedOutput)) {
        return ptr->size() == 0;
    }
    return false;
}

size_t WareContainer::wareAwailableAdditingAmount(std::string ware, size_t count, bool ignoreAllowed) {
    if(count > 0 && (ignoreAllowed || containsAllowedInput(ware))) {
        return std::min(m_capacity - amount(), count);
    }
    return 0;
}

size_t WareContainer::wareAwailableRemovingAmount(size_t index, size_t count, bool ignoreAllowed) {
    if(index < m_data.size()) {
        auto& w = m_data[index];
        if(ignoreAllowed || containsAllowedOutput(w.first)) {
            return std::min(w.second, count);
        }
    }
    return 0;
}

size_t WareContainer::addWare(std::string ware, size_t count, bool ignoreAllowed) {
    count = wareAwailableAdditingAmount(ware, count, ignoreAllowed);
    if(count > 0) {
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
    return count;
}

size_t WareContainer::removeWare(size_t index, size_t count, bool ignoreAllowed) {
    count = wareAwailableRemovingAmount(index, count, ignoreAllowed);
    if(count > 0) {
        auto& w = m_data[index];
        count = std::min(w.second, count);
        w.second -= count;

        if(w.second == 0)
            m_data.erase(m_data.begin() + index);

        return count;
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

size_t WareContainer::capacity() const {
    return m_capacity;
}

size_t WareContainer::setCapacity(const size_t &capacity) {
    return m_capacity = std::max(capacity, amount());
}

std::ostream &operator<<(std::ostream &stream, const WareContainer::Allowed &allowed) {
    if(std::get_if<WareContainer::all_allowed_t>(&allowed)) {
        stream << "AllAllowed";
    } else {
        if(const auto ptr = std::get_if<std::vector<std::string>>(&allowed)) {
            size_t i = 0;
            stream << "[";
            for(const auto& a : *ptr) {
                stream << a;
                if(i < ptr->size() - 1) {
                    stream << ", ";
                }
                ++i;
            }
            stream << "]";
        }
    }
    return stream;
}
