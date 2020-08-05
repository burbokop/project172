#ifndef KABSTRACTFACTORY_H
#define KABSTRACTFACTORY_H



#include <map>
#include <functional>

#include <src/utility/ktype.h>

/**
 * @brief The KAbstractFactory class provides standart abstract factory
 * @details Template parameter <b>BaseClass</b> defines witch type is handled by specific instance of factory.
 * Factory handle only <b>BaseClass</b> type and types inherited by <b>BaseClass</b>.
 * Factory can not work with interfaces because them can not be created, but base type can be interface.
 * Template parameter <b>KeyType</b> defines witch type to use for store type names (is you use QString, std::string, or other type witch is casted from <b>const char*</b> typeName is set automaticaly by using KType class. Otherwise you mast set is manualy.)
 *
 * @note KAbstractFactory is available whithout Qt.
 */

template<typename KeyType, typename BaseClass>
class KAbstractFactory {
    typedef std::map<KeyType, std::function<BaseClass*()>> CreaterMap;

    CreaterMap creaters;
    std::map<BaseClass*, KeyType> typeNames;
public:
    KAbstractFactory();
    /**
     * @brief create function creates object with type name <b>typeName</b>.
     * @param typeName
     * @return pointer to new object
     */
    BaseClass *create(const KeyType &typeName);

    /**
     * @brief type function provide getting type name from object pointer.
     * @param object
     * @return type name
     */
    KeyType type(BaseClass *object) const;

    /**
     * @brief registerType function provide registering type <b>T</b>.
     * @details After calling this function current instance of factory can create instances of <b>T</b>.
     * @param typeName
     * @return type name passed as paremeter without changes
     */
    template<typename T>
    KeyType registerType(const KeyType &typeName);

    /**
     * @brief registerType overload provide registering type <b>T</b> but use KType for setting type name.
     * @return type name
     */
    template<typename T>
    KeyType registerType();


    /**
     * @brief clear factory
     */
    void clear() {
        creaters.clear();
        typeNames.clear();
    }
};

template<typename KeyType, typename BaseClass>
KAbstractFactory<KeyType, BaseClass>::KAbstractFactory() {}

template<typename KeyType, typename BaseClass>
KeyType KAbstractFactory<KeyType, BaseClass>::type(BaseClass *object) const {
    auto it = typeNames.find(object);
    if(it != typeNames.end())
        return it->second;
    return KeyType();
}

template<typename KeyType, typename BaseClass>
template<typename T>
KeyType KAbstractFactory<KeyType, BaseClass>::registerType() {
    return registerType<T>(KType<T>().c_str());
}

template<typename KeyType, typename BaseClass>
template<typename T>
KeyType KAbstractFactory<KeyType, BaseClass>::registerType(const KeyType &typeName) {
    creaters[typeName] = []() {
        return new T();
    };
    return typeName;
}

template<typename KeyType, typename BaseClass>
BaseClass *KAbstractFactory<KeyType, BaseClass>::create(const KeyType &typeName) {
    if(creaters.find(typeName) == creaters.end()) {
        throw std::runtime_error((std::string(__PRETTY_FUNCTION__) + " unknown key.").c_str());
        return nullptr;
    }
    auto obj = creaters[typeName]();
    typeNames[obj] = typeName;
    return obj;
}

#endif // KABSTRACTFACTORY_H
