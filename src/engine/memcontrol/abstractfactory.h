#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H



#include <map>
#include <functional>

#include "../type.h"

/**
 * @brief The AbstractFactory class provides standart abstract factory
 * @details Template parameter <b>BaseClass</b> defines witch type is handled by specific instance of factory.
 * Factory handle only <b>BaseClass</b> type and types inherited by <b>BaseClass</b>.
 * Factory can not work with interfaces because them can not be created, but base type can be interface.
 * Template parameter <b>KeyType</b> defines witch type to use for store type names (is you use QString, std::string, or other type witch is casted from <b>const char*</b> typeName is set automaticaly by using KType class. Otherwise you mast set is manualy.)
 *
 * @note AbstractFactory is available whithout Qt.
 */

namespace e172 {

template<typename KeyType, typename BaseClass>
class AbstractFactory {
    typedef std::map<KeyType, std::function<BaseClass*()>> CreaterMap;

    CreaterMap creaters;
    std::map<BaseClass*, KeyType> typeNames;
public:
    AbstractFactory();
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
AbstractFactory<KeyType, BaseClass>::AbstractFactory() {}

template<typename KeyType, typename BaseClass>
KeyType AbstractFactory<KeyType, BaseClass>::type(BaseClass *object) const {
    auto it = typeNames.find(object);
    if(it != typeNames.end())
        return it->second;
    return KeyType();
}

template<typename KeyType, typename BaseClass>
template<typename T>
KeyType AbstractFactory<KeyType, BaseClass>::registerType() {
    return registerType<T>(Type<T>::name);
}

template<typename KeyType, typename BaseClass>
template<typename T>
KeyType AbstractFactory<KeyType, BaseClass>::registerType(const KeyType &typeName) {
    creaters[typeName] = []() {
        return new T();
    };
    return typeName;
}

template<typename KeyType, typename BaseClass>
BaseClass *AbstractFactory<KeyType, BaseClass>::create(const KeyType &typeName) {
    const auto it = creaters.find(typeName);
    if(it == creaters.end()) {
        return nullptr;
    }
    auto obj = it->second();
    typeNames[obj] = typeName;
    return obj;
}


}


#endif // ABSTRACTFACTORY_H
