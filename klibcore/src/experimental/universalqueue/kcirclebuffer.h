#ifndef KCIRCLEBUFFER_H
#define KCIRCLEBUFFER_H


#include <vector>


/**
 * @brief The KCircleBuffer class provides standart circule buffer
 * @details This tool can be used for transfering data betwen threads.
 * Size of this circule buffer is limited and is defined in constructor.
 * This class has interface as standart queue.
 *
 * @note This class is available whithout Qt.
 */
template<class T>
class KCircleBuffer {
public:
    KCircleBuffer(int size) : m_size(size), m_data(size) {}
    /**
     * @brief push function provides pushing one element
     * @param value
     * @return true if pushing succesfully
     */
    bool push(const T& value);
    /**
     * @brief pop function provides dequeueing one element
     * @param ok - pointer to bool witch becomes true after call if operation is succesfully
     * @return dequeued value
     */
    T pop(bool *ok = nullptr);
    /**
     * @brief isEmpty getter
     * @return true if buffer is empty
     */
    bool isEmpty() const;
private:
    int write_pos = 0;
    int read_pos = 0;
    bool m_isEmpty = true;
    int m_size;
    std::vector<T> m_data;
};

template<class T>
bool KCircleBuffer<T>::push(const T &value) {
    if ((write_pos == read_pos) && !m_isEmpty) {
        return false;
    }
    m_data[write_pos] = value;
    write_pos = (write_pos+1) % m_size;
    m_isEmpty = false;
    return true;
}

template<class T>
T KCircleBuffer<T>::pop(bool *ok) {
    if (m_isEmpty){
        if (ok!=nullptr) *ok = false;
        return T();
    }
    int rpos = read_pos;
    read_pos =  (read_pos+1) % m_size;
    if (read_pos == write_pos) m_isEmpty = true;
    if (ok!=nullptr) *ok = true;
    return m_data[rpos];
}

template<class T>
bool KCircleBuffer<T>::isEmpty() const {
    return m_isEmpty;
}


#endif // KCIRCLEBUFFER_H
