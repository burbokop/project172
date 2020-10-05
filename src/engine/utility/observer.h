#ifndef OBSERVER_H
#define OBSERVER_H

#include <functional>
#include <map>
#include <memory>

namespace e172 {

template <typename T>
class Observer {
    struct Data {
        T value;
        size_t nextConnectionId = 0;
        std::map<size_t, std::function<void(const T&)>> callbacks;
    };
    std::shared_ptr<Data> m_data;
public:
    Observer() {}
    Observer(const T& value) {
        operator=(value);
    }

    size_t connect(const std::function<void(const T&)> &callback) {
        if(m_data) {
            m_data->callbacks[++m_data->nextConnectionId] = callback;
            callback(m_data->value);
            return m_data->nextConnectionId;
        }
        return 0;
    }
    template<typename C>
    size_t connect(C *object, void(C::*callback)(const T&)) {
        return onChanged([object, callback](const auto& v){ (object->*callback)(v); });
    }

    bool disconnect(size_t connectionId) {
        if(m_data) {
            const auto it = m_data->callbacks.find(connectionId);
            if(it == m_data->callbacks.end())
                return false;

            m_data->callbacks.erase(it);
            return true;
        }
        return false;
    }

    void operator=(const T& value) {
        if(!m_data) {
            m_data = std::make_shared<Data>();
        }

        if(m_data->value == value)
            return;

        m_data->value = value;
        for(const auto &c : m_data->callbacks) {
            if(c.second)
                c.second(value);
        }
    }

    operator T() const {
        if(m_data)
            return m_data->value;

        return T();
    }
    T value() const { return operator T(); };

    bool isValid() const { return m_data; }



};

template<typename K, typename V>
inline std::map<K, e172::Observer<V>> toObserverMap(const std::map<K, V> &src) {
    std::map<K, e172::Observer<V>> result;
    for(const auto &s : src) {
        result[s.first] = s.second;
    }
    return result;
}


}

#endif // OBSERVER_H
