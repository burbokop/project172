#ifndef OBJECT_H
#define OBJECT_H

#include <type_traits>

#define UNUSED(expr) do { (void)(expr); } while (0)

namespace e172 {


template<typename T, typename P>
inline P verbatim_cast(T value) { return reinterpret_cast<P*>(&value)[0]; }


class Object {
    bool m_liveInHeap = false;
protected:

public:
    Object();



    template <typename Type>
    [[deprecated("Use instanceOf instead")]]
    bool is() {
        return dynamic_cast<Type>(this) != nullptr;
    }

    template <typename Type>
    bool instanceOf() {
        typedef typename std::remove_pointer<Type>::type no_ptr_t;
        return dynamic_cast<no_ptr_t*>(this) != nullptr;
    }


    template <typename Type>
    [[deprecated("Use !instanceOf instead")]]
    bool isNot() {
        return dynamic_cast<Type>(this) == nullptr;
    }


    virtual ~Object();
    bool liveInHeap() const;
};

}
#endif // OBJECT_H
