#ifndef KUNIVERSALQUEUE_H
#define KUNIVERSALQUEUE_H

#include <src/utility/ktype.h>

#include <map>

#include "kcirclebuffer.h"
#include "kvoidhandle.h"

/**
 * @brief The KUniversalQueue class provides queue an instance of which can work with different types
 *
 * @note This class is available whithout Qt
 * @note You can consider thet this class is analog of QVariant but with queue functional
 */
class KUniversalQueue {
    std::map<int, KVoidHandle*> buffers;
    int m_capacity = 0;

    template<typename T>
    auto checkBuffer(int id);
public:
    /**
     * @brief KUniversalQueue constructor
     * @param capacity - size of buffers (in not expandable)
     */
    KUniversalQueue(int capacity = 256);


    /**
     * @brief containsItemType function says if queue contains element of type <b>T</b>
     * @return true if queue contains item of type <b>T</b>
     */
    template<typename T>
    bool containsItemType();

    /**
     * @brief enqueue function need for pushing items to queue
     * @param value - value that will be pushed
     */
    template<typename T>
    bool enqueue(const T &value);

    /**
     * @brief dequeue function takes one front item of type <b>T</b>
     * @param ok - pointer to bool. After calling this function contains true if success else false
     * @return taken item if one is exist, else returns default value
     */
    template<typename T>
    T dequeue(bool *ok = nullptr);
    ~KUniversalQueue();

    /**
     * @brief capacity getter
     * @return
     */
    int capacity() const;
};

template<typename T>
bool KUniversalQueue::containsItemType() {
    auto id = KType<T>().hash();
    auto it = buffers.find(id);

    if(it == buffers.end()) {
        return false;
    }
    return !reinterpret_cast<KCircleBuffer<T>*>(it->second->data())->isEmpty();
}

template<typename T>
auto KUniversalQueue::checkBuffer(int id) {
    auto c = capacity();
    auto it = buffers.find(id);
    if(it == buffers.end()) {
        it = buffers.insert(buffers.begin(), std::pair<int, KVoidHandle*>(id, new KVoidHandle([c](){ return new KCircleBuffer<T>(c); }, [](void *data) { delete reinterpret_cast<KCircleBuffer<T>*>(data); })));
    }
    return it;
}


template<typename T>
bool KUniversalQueue::enqueue(const T &value) {
    auto id = KType<T>().hash();
    auto it = checkBuffer<T>(id);
    return reinterpret_cast<KCircleBuffer<T>*>(it->second->data())->push(value);
}

template<typename T>
T KUniversalQueue::dequeue(bool *ok) {
    auto id = KType<T>().hash();
    auto it = buffers.find(id);

    if(it == buffers.end()) {
        if(ok != nullptr) *ok = false;
        return T();
    }
    return reinterpret_cast<KCircleBuffer<T>*>(it->second->data())->pop(ok);
}


#endif // KUNIVERSALQUEUE_H
