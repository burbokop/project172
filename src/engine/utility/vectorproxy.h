#ifndef VECTORPROXY_H
#define VECTORPROXY_H

#include <vector>

namespace e172 {


template<typename T>
class VectorProxy {
    std::vector<std::vector<T>*> m_pointers;
public:
    VectorProxy(const std::vector<std::vector<T>*> &pointers) {
        m_pointers = pointers;
    }

    size_t size() const {
        size_t sum = 0;
        for(auto p : m_pointers) {
            sum += p->size();
        }
        return sum;
    }

    T &operator[](size_t index) {
        size_t pi = 0;
        while(index >= m_pointers[pi]->size()) {
            index -= m_pointers[pi]->size();
            ++pi;
        }
        return (*m_pointers[pi])[index];
    }

    T operator[](size_t index) const {
        size_t pi = 0;
        while(index >= m_pointers[pi]->size()) {
            index -= m_pointers[pi]->size();
            ++pi;
        }
        return (*m_pointers[pi])[index];
    }

};

}
#endif // VECTORPROXY_H
