#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "variant.h"
#include <queue>
#include <memory>

namespace e172 {

class Promice {
public:
    enum State {
        InProcess,
        Done,
        Failed
    };
protected:
    std::function<void()> m_done;
    std::function<void()> m_fail;
    State m_state = InProcess;
public:
    void onDone(const std::function<void()> &callback) { m_done = callback; if(Done) { callback(); } }
    void onFail(const std::function<void()> &callback) { m_fail = callback; if(Failed) { callback(); } }
    State state() const { return m_state; }
};

class MessageQueuePromice : public Promice {
    template <typename IdType, typename ValueType>
    friend class MessageQueue;
};

class MessageQueuePrivate {
    template <typename IdType, typename ValueType>
    friend class MessageQueue;

    static void throwExeption(const std::string &exeption);
    static void warningExeption(const std::string &exeption);
};

template <typename IdType, typename ValueType>
class MessageQueue {
    struct MessageType {
        ValueType value;
        int loop_count = 0;
        std::shared_ptr<MessageQueuePromice> promice;
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

    static std::string produceExeption(const IdType &id, const ValueType &value) {
        std::stringstream ss;
        ss << "MessageQueue: message flushed ";
        constexpr bool hasAny =
                sfinae::StreamOperator::exists<std::ostream, IdType>::value
                || sfinae::StreamOperator::exists<std::ostream, ValueType>::value;
        if constexpr (sfinae::StreamOperator::exists<std::ostream, IdType>::value) {
            ss << "(message id: " << id;
        }
        if constexpr (sfinae::StreamOperator::exists<std::ostream, ValueType>::value) {
            ss << ", value: " << value;
        }
        if constexpr(hasAny) {
            ss << ")";
        }
        ss << ".";
        return ss.str();
    }


    static void filterList(std::list<MessageType> *list, ExceptionHandlingMode exceptionHandlingMode, const IdType &id) {
        auto it = list->begin();
        while(it != list->end()) {
            if(it->loop_count-- <= 0) {
                auto message = *it;
                if(message.promice) {
                    if(message.promice->m_fail)
                        message.promice->m_fail();
                    message.promice->m_state = Promice::Failed;
                }

                if(exceptionHandlingMode != IgnoreException) {
                    if(exceptionHandlingMode == ThrowException) {
                        MessageQueuePrivate::throwExeption(produceExeption(id, message.value));
                    } else if(exceptionHandlingMode == WarningException) {
                        MessageQueuePrivate::warningExeption(produceExeption(id, message.value));
                    }
                }
                it = list->erase(it);
            } else {
                ++it;
            }
        }
    }

    bool containsMessage(const IdType &id) {
        const auto it = m_data.find(id);
        if(it == m_data.end())
            return false;

        return it->second.queue.size() > 0;
    }

public:
    MessageQueue() {}


    void popMessage(const IdType &id, const std::function<void(const ValueType&)>& callback) {
        const auto it = m_data.find(id);
        if(it == m_data.end())
            return;

        while(it->second.queue.size() > 0) {
            const auto message = it->second.queue.front();
            it->second.queue.pop_front();

            callback(message.value);

            if(message.promice) {
                if(message.promice->m_done)
                    message.promice->m_done();

                message.promice->m_state = Promice::State::Done;
            }
        }
    }

    template<typename C>
    void popMessage(const IdType &id, C *object, void(C::*callback)(const ValueType&)) {
        popMessage(id, [object, callback](auto v) { (object->*callback)(v); });
    }

    std::shared_ptr<Promice> emitMessage(const IdType &id, const ValueType &value) {
        const auto p = std::make_shared<MessageQueuePromice>();
        m_data[id].queue.push_back(MessageType { value, m_messageLifeTime, p });
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
                        message.promice->m_state = Promice::Done;
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
