#ifndef OBJECT_H
#define OBJECT_H


#define UNUSED(expr) do { (void)(expr); } while (0)

template<typename T, typename P>
inline P verbatim_cast(T value) { return reinterpret_cast<P*>(&value)[0]; }


class Object {
protected:

public:
    Object();

    template <typename Type>
    bool is() {
        return dynamic_cast<Type>(this) != nullptr;
    }


    template <typename Type>
    bool isNot() {
        return dynamic_cast<Type>(this) == nullptr;
    }


    virtual ~Object();
};

#endif // OBJECT_H
