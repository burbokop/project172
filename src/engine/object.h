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
    inline bool instanceOf() const { return cast<Type>(); }

    template <typename Type>
    inline bool instanceOf() { return cast<Type>(); }

    template <typename Type>
    inline typename std::remove_pointer<Type>::type *cast() const {
        typedef typename std::remove_pointer<Type>::type no_ptr_t;
        return dynamic_cast<const no_ptr_t*>(this);
    }

    template <typename Type>
    inline typename std::remove_pointer<Type>::type *cast() {
        typedef typename std::remove_pointer<Type>::type no_ptr_t;
        return dynamic_cast<no_ptr_t*>(this);
    }

    virtual ~Object();
    bool liveInHeap() const;
};

struct alive_t {};

static const inline alive_t Alive;

bool operator ==(Object *object, const alive_t&);
bool operator ==(const alive_t&, Object *object);
bool operator !=(Object *object, const alive_t&);
bool operator !=(const alive_t&, Object *object);


}
#endif // OBJECT_H
