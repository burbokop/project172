#ifndef KTYPE_H
#define KTYPE_H


#include <string>

namespace e172 {

class TypePrivate {
    template<typename> friend struct Type;
    static std::string demangle(const std::string &typeName);
};

template <typename T>
struct Type { static inline const std::string name = TypePrivate::demangle(typeid (T).name()); };


}

#endif // KTYPE_H
