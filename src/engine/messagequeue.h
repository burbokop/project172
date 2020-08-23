#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "variant.h"
#include <queue>

namespace e172 {

class Promice {
protected:
    std::function<void()> m_done;
    std::function<void()> m_fail;
public:
    void onDone(const std::function<void()> &callback) { m_done = callback; }
    void onFail(const std::function<void()> &callback) { m_fail = callback; }
};

class MessageBusPromice : public Promice {
    template <typename IdType, typename ValueType>
    friend class MessageBus;
};

class MessageBusPrivate {
    template <typename IdType, typename ValueType>
    friend class MessageBus;

    static void throwExeption(const std::string &exeption);
    static void warningExeption(const std::string &exeption);
};

template <typename IdType, typename ValueType>
class MessageBus {
    struct MessageType {
        ValueType value;
        int loop_count = 0;
        MessageBusPromice *promice = nullptr;
    };

    struct IdentifiedData {
        std::list<MessageType> queue;
        std::list<std::function<void(const ValueType &)>> functions;
    };

    std::map<IdType, IdentifiedData> m_data;
    int m_messageLifeTime = 0;
public:
    enum ExceptionHandlingMode {
        IgnoreException,
        WarningException,
        ThrowException
    };
private:
    ExceptionHandlingMode m_exceptionHandlingMode = IgnoreException;
public:

    static void filterList(std::list<MessageType> *list, ExceptionHandlingMode exceptionHandlingMode, const IdType &id) {
        auto it = list->begin();
        while(it != list->end()) {
            if(it->loop_count-- <= 0) {
                auto message = *it;
                MessageBusPrivate::warningExeption("+++ " + message.value.toString());
                if(message.promice) {
                    if(message.promice->m_fail)
                        message.promice->m_fail();
                    delete message.promice;
                }

                if(exceptionHandlingMode != IgnoreException) {
                    std::stringstream ss;
                    ss << "MessageBus: message flushed (message id: " << id << ")";
                    if(exceptionHandlingMode == ThrowException) {
                        MessageBusPrivate::throwExeption(ss.str());
                    } else if(exceptionHandlingMode == WarningException) {
                        MessageBusPrivate::warningExeption(ss.str());
                    }
                }
                it = list->erase(it);
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

        return it->second.queue.size() > 0;
    }

    ValueType popMessage(const IdType &id, bool *ok = nullptr) {
        if(ok)
            *ok = false;
        const auto it = m_data.find(id);
        if(it == m_data.end())
            return ValueType();

        if(it->second.queue.size() > 0) {
            const auto message = it->second.queue.front();
            it->second.queue.pop_front();

            if(message.promice) {
                if(message.promice->m_done)
                    message.promice->m_done();
                delete message.promice;
            }

            if(ok)
                *ok = false;
            return message.value;
        }
        return ValueType();
    }
    Promice *emitMessage(const IdType &id, const ValueType &value) {
        const auto p = new MessageBusPromice();
        m_data[id].queue.push_back(MessageType { value, 0, p });
        return p;
    }
    void flushMessages() {
        for(auto &p : m_data) {
            filterList(&p.second.queue, m_exceptionHandlingMode, p.first);
        }
    }

    void invokeInternalFunctions() {
        for(auto d : m_data) {
            if(d.second.functions.size() > 0) {
                while(d.second.queue.size() > 0) {
                    const auto message = d.second.queue.front();
                    for(auto func : d.second.functions) {
                        func(message.value);
                    }
                    if(message.promice) {
                        message.promice->m_done();
                        delete message.promice;
                    }

                    d.second.queue.pop_front();
                }
            }
        }
    }

    int messageLifeTime() const { return m_messageLifeTime; }
    void setMessageLifeTime(int messageLifeTime) { m_messageLifeTime = messageLifeTime; }

    void setExceptionHandlingMode(const ExceptionHandlingMode &exceptionHandlingMode) { m_exceptionHandlingMode = exceptionHandlingMode; };
};

}
#endif // MESSAGEQUEUE_H
