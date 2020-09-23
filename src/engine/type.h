#ifndef KTYPE_H
#define KTYPE_H

#include <typeinfo>
#include <string>

namespace e172 {

class TypePrivate {
    template<typename> friend class Type;
    static std::string demangle(const std::string &typeName);
};

template <typename T>
class Type {
    static inline const std::string m_name = TypePrivate::demangle(typeid (T).name());
    static inline const size_t m_hash = typeid (T).hash_code();
public:
    static inline std::string name() { return m_name.size() > 0 ? m_name : TypePrivate::demangle(typeid (T).name()); }
    static inline size_t hash() { return m_hash ? m_hash : typeid (T).hash_code(); }
};


}

#endif // KTYPE_H
