#ifndef CYCLICITERATOR_H
#define CYCLICITERATOR_H

#include <list>
#include <algorithm>

namespace e172 {

template <typename T>
class CyclicList {
    std::list<T> m_container;
    typename std::list<T>::iterator m_auto_it = m_container.begin();
public:
    CyclicList() {}
    operator std::list<T>() const { return m_container; }

    auto begin() const { return m_container.begin(); }
    auto begin() { return m_container.begin(); }
    auto end() const { return m_container.end(); }
    auto end() { return m_container.end(); }
    auto size() const { return m_container.size(); }

    void nextCycle() {
        if(m_auto_it == m_container.end()) {
            m_auto_it = m_container.begin();
            return;
        }

        if(++m_auto_it == m_container.end()) {
            m_auto_it = m_container.begin();
        }
    }

    T cyclicValue(const T& defaultValue = T()) const {
        return m_auto_it == m_container.end() ? defaultValue : *m_auto_it;
    };

    template<typename It>
    auto erase(It it) {
        bool do_reset = m_auto_it == it;
        it = m_container.erase(it);
        if(do_reset) {
            m_auto_it = it;
        }
        return it;
    }

    template<typename Value>
    void remove(const Value &value) {
        const auto it = std::find(m_container.begin(), m_container.end(), value);
        if(it != m_container.end())
            erase(it);
    }

    void push_back(const T &value) { m_container.push_back(value); }

};

}
#endif // CYCLICITERATOR_H
