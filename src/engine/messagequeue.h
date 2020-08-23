#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "variant.h"
#include <queue>

namespace e172 {

template <typename IdType, typename ValueType>
class MessageBus {
    struct MessageType {
        ValueType value;
        int loop_count = 0;
    };

    struct IdentifiedData {
        std::list<MessageType> queue;
        std::list<std::function<void(const ValueType &)>> functions;
    };

    std::map<IdType, IdentifiedData> m_data;
    int m_messageLifeTime = 0;


public:
    static void filterList(std::list<MessageType> *list) {
        auto it = list->begin();
        while(it != list->end()) {
            if(it->loop_count-- <= 0) {
                it = list->erase(it);
            } else {
                ++it;
            }
        }
    }

    static void filterMap(std::map<IdType, std::list<MessageType>> *map) {
        auto it = map->begin();
        while(it != map->end()) {
            filterList(&it.second);
            if(it.second.size() <= 0) {
                it = map->erase(it);
            } else {
                ++it;
            }
        }
    }


    MessageBus() {}
    bool containsMessage(const IdType &id) {
        const auto it = m_data.find(id);
        if(it == m_data.end())
            return false;

        return it.second.size() > 0;
    }
    ValueType popMessage(const IdType &id, bool *ok = nullptr) {
        if(ok)
            *ok = false;
        const auto it = m_data.find(id);
        if(it == m_data.end())
            return ValueType();

        if(it.second.size() > 0) {
            const auto result = it.second.front();
            it.second.pop();
            if(ok)
                *ok = false;
            return result.value;
        }
    }
    void emitMessage(const IdType &id, const ValueType &value) {
        m_data[id].push({ value, 0 });
    }
    void flushMessages() {
        filterMap(&m_data);
    }

    void invokeInternalFunctions() {
        for(auto d : m_data) {
            if(d.second.functions.size() > 0) {
                while(d.second.queue.size() > 0) {
                    const auto value = d.second.queue.front().value;
                    for(auto func : d.second.functions) {
                        func(value);
                    }
                    d.second.queue.pop();
                }
            }
        }
    }

    int messageLifeTime() const { return m_messageLifeTime; }
    void setMessageLifeTime(int messageLifeTime) { m_messageLifeTime = messageLifeTime; }

};

}
#endif // MESSAGEQUEUE_H
