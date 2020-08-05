#ifndef KVOIDHANDLE_H
#define KVOIDHANDLE_H

#include <functional>


/**
 * @brief The KVoidHandle class provide containing common data and instructions how to delete this data
 * @note This class is available whithout Qt.
 */
class KVoidHandle {
    void *m_data = nullptr;
    std::function<void (void*)> destructor;
public:
    /**
     * @brief KVoidHandle constructor
     * @param constructor that construct stored data
     * @param destructor that destruct stored data
     */
    KVoidHandle(std::function<void *()> constructor, std::function<void (void*)> destructor);
    ~KVoidHandle();

    /**
     * @brief data getter
     * @return void pointer that can be casted by reinterpret_cast to any type
     */
    void *data() const;
};

#endif // KVOIDHANDLE_H
