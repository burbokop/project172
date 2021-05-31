#include "warecontainer.h"

#include <algorithm>

size_t WareContainer::amount() const {
    size_t sum = 0;
    for(auto s : m_data) {
        sum += std::get<1>(s);
    }
    return sum;
}

bool WareContainer::isInputAllowed(const std::string &wareName) const {
    if(std::get_if<all_allowed_t>(&m_allowedInput)) {
        return true;
    } else {
        if(const auto ptr = std::get_if<std::vector<std::string>>(&m_allowedInput)) {
            return std::find(ptr->begin(), ptr->end(), wareName) != ptr->end();
        }
    }
    return false;
}

bool WareContainer::isOutputAllowed(const std::string &wareName) const {
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
    if(count > 0 && (ignoreAllowed || isInputAllowed(ware))) {
        return std::min(m_capacity - amount(), count);
    }
    return 0;
}

size_t WareContainer::wareAwailableRemovingAmount(size_t index, size_t count, bool ignoreAllowed) {
    if(index < m_data.size()) {
        auto& w = m_data[index];
        if(ignoreAllowed || isOutputAllowed(std::get<0>(w))) {
            return std::min(std::get<1>(w), count);
        }
    }
    return 0;
}

size_t WareContainer::addWare(std::string ware, size_t count, bool ignoreAllowed) {
    count = wareAwailableAdditingAmount(ware, count, ignoreAllowed);
    if(count > 0) {
        bool found = false;
        for(size_t i = 0; i < m_data.size(); ++i) {
            if(std::get<0>(m_data[i]) == ware) {
                std::get<1>(m_data[i]) += count;
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
        count = std::min(std::get<1>(w), count);
        std::get<1>(w) -= count;

        if(std::get<1>(w) == 0)
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
    if(index < m_data.size()) {
        return WareInfo(std::get<0>(m_data[index]), std::get<1>(m_data[index]), true);
    }
    return WareInfo(std::string(), 0, false);
}

size_t WareContainer::capacity() const {
    return m_capacity;
}

double WareContainer::full() const {
    if(const auto c = capacity()) {
        return double(amount()) / double(c);
    } else {
        return 0;
    }
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
