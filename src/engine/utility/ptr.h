#ifndef PTR_H
#define PTR_H

#include <src/engine/object.h>
#include <src/engine/sfinae.h>

namespace e172 {


template <typename T>
class ptr {
    template<typename A> friend class ptr;
    T *m_data;
    Object::LifeInfo m_lifeInfo;
public:
    E172_SFINAE_METHOD_CHECKER(lifeInfo)
    ptr() {}
    ptr(const std::nullptr_t&) {}
    template<typename ...Args>
    static ptr<T> make(Args ...args) { return new T(args...); }

    template<typename TT>
    ptr(TT* data) {
        m_data = data;
        static_assert (has_lifeInfo_method<TT>::value, "T must be inherited by e172::Object");
        if constexpr(has_lifeInfo_method<TT>::value) {
            if(m_data)
                m_lifeInfo = m_data->lifeInfo();
        }
    }
    template<typename O>
    ptr(const ptr<O>& p) { operator=(p); }
    template<typename O>
    void operator=(const ptr<O> &p) {
        m_data = p.m_data;
        m_lifeInfo = p.m_lifeInfo;
    }
    T *operator->() { return m_data; };
    T *operator->() const { return m_data; };
    T* data() const { return m_data; }

    operator bool() const { return m_lifeInfo; }
};

template<typename T>
struct smart_ptr_type {
    typedef typename std::remove_pointer<T>::type no_ptr_t;
    typedef typename ptr<no_ptr_t>::template has_lifeInfo_method<no_ptr_t> is_object;
    typedef typename std::conditional<is_object::value, ptr<no_ptr_t>, no_ptr_t*>::type type;
};


template <typename T>
void destroy(const e172::ptr<T> &ptr) {
    delete ptr.operator->();
}

template<typename T, typename A>
auto smart_cast(const ptr<A> &p) {
    typedef typename smart_ptr_type<T>::type return_type;
    if(p) {
        return return_type(p->template cast<T>());
    }
    return return_type();
}

template<typename T, typename A>
auto smart_cast(A *p) {
    typedef typename std::remove_pointer<T>::type no_ptr_t;
    typedef typename smart_ptr_type<T>::type return_type;
    if(p) {
        return return_type(dynamic_cast<no_ptr_t*>(p));
    }
    return return_type();
}


}

template<typename A, typename B>
bool operator ==(const e172::ptr<A> &ptr0, const e172::ptr<B> &ptr1) {
    return ptr0.data() == ptr1.data();
}
template<typename A, typename B>
bool operator !=(const e172::ptr<A> &ptr0, const e172::ptr<B> &ptr1) {
    return ptr0.data() != ptr1.data();
}
template<typename A, typename B>
bool operator ==(const e172::ptr<A> &ptr0, B *ptr1) {
    return ptr0.data() == ptr1;
}
template<typename A, typename B>
bool operator !=(const e172::ptr<A> &ptr0, B *ptr1) {
    return ptr0.data() != ptr1;
}
template<typename A, typename B>
bool operator ==(A *ptr0, const e172::ptr<B> &ptr1) {
    return ptr0 == ptr1.data();
}
template<typename A, typename B>
bool operator !=(A *ptr0, const e172::ptr<B> &ptr1) {
    return ptr0 != ptr1.data();
}

#endif // PTR_H
