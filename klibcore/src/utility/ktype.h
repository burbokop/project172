#ifndef KTYPE_H
#define KTYPE_H


#include <string>

#ifdef QT_CORE_LIB
    #include <QString>
#endif

/**
 * @brief The KType class provides getting human friendly type name string.
 * @details Instance of this class contans human friendly type name of type <b>T</b>.
 * KType class provides operators for translation type to QString, std::string and const char*.\n
 * Also you can get hash of type for some indexing.
 *
 * @note KType is available whithout Qt but hash option need Qt. Without Qt hash only return 0.
 */
template <typename T>
class KType {
    std::string m_typeName;
    uint64_t m_hash;
public:
    KType();

#ifdef QT_CORE_LIB
    operator QString() const;
    QString typeName() const;
    QString toString() const;
#endif
    operator std::string() const;
    std::string toStdString() const;
    operator const char*() const;
    const char *c_str() const;

    /**
     * @brief hash
     * @return hash of type name
     */
    uint64_t hash() const;
};

class KTypeAdditional {
public:
    static uint64_t hash64(const std::string& string);
    static std::string demangle(const std::string &typeName);
};


template<typename T>
KType<T>::KType() {
    m_typeName = KTypeAdditional::demangle(typeid (T).name());
    m_hash = KTypeAdditional::hash64(m_typeName);
}

#ifdef QT_CORE_LIB
template<typename T>
QString KType<T>::toString() const {
    return QString::fromStdString(m_typeName);
}

template<typename T>
KType<T>::operator QString() const {
    return QString::fromStdString(m_typeName);
}

template<typename T>
QString KType<T>::typeName() const {
    return QString::fromStdString(m_typeName);
}

#endif

template<typename T>
KType<T>::operator const char*() const {
    return m_typeName.c_str();
}

template<typename T>
uint64_t KType<T>::hash() const {
    return m_hash;
}

template<typename T>
KType<T>::operator std::string() const {
    return m_typeName;
}

template<typename T>
std::string KType<T>::toStdString() const {
    return m_typeName;
}

template<typename T>
const char *KType<T>::c_str() const {
    return m_typeName.c_str();
}


#endif // KTYPE_H
