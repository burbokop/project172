#ifndef OBJECT_H
#define OBJECT_H


#define UNUSED(expr) do { (void)(expr); } while (0)

template<typename T, typename P>
inline P verbatim_cast(T value) { return reinterpret_cast<P*>(&value)[0]; }


class Object {
public:
    Object();
};

#endif // OBJECT_H
