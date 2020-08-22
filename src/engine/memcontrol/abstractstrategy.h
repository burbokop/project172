#ifndef KMODULESWITCH_H
#define KMODULESWITCH_H

#include "abstractfactory.h"

#include <src/kmacro.h>
#include <list>

namespace e172 {


template<typename KeyType, typename Base>
class AbstractStrategy {
    AbstractFactory<KeyType, Base> factory;
    std::list<KeyType> m_moduleNames;
    KeyType m_activeModuleName;
    Base *m_activeModule = nullptr;

    void addTypeName(const KeyType &name) {
        const auto it = std::find(m_moduleNames.begin(), m_moduleNames.end(), name);
        if(it == m_moduleNames.end()) {
            m_moduleNames.push_back(name);
        }
    }
public:
    AbstractStrategy() {}

    bool activate(const KeyType &moduleName);
    bool deactivateCurrent();

    template<typename T>
    void registerType() {
        addTypeName(factory.template registerType<T>());
    }

    template<typename T>
    void registerType(KeyType moduleName) {
        addTypeName(factory.template registerType<T>(moduleName));
    }
    std::list<KeyType> moduleNames() const;
    KeyType activeModuleName() const;
    Base *activeModule() const;
};

template<typename KeyType, typename Base>
bool AbstractStrategy<KeyType, Base>::activate(const KeyType &moduleName) {
    if(moduleName == m_activeModuleName) {
        return false;
    }

    if(auto newObject = factory.create(moduleName)) {
        if(m_activeModule) {
            delete m_activeModule;
        }

        m_activeModule = newObject;
        m_activeModuleName = moduleName;
        return true;
    }
    return false;
}

template<typename KeyType, typename Base>
bool AbstractStrategy<KeyType, Base>::deactivateCurrent() {
    if(m_activeModule) {
        delete m_activeModule;
        m_activeModule = nullptr;
        m_activeModuleName = KeyType();
        return true;
    }
    return false;
}

template<typename KeyType, typename Base>
std::list<KeyType> AbstractStrategy<KeyType, Base>::moduleNames() const {
    return m_moduleNames;
}

template<typename KeyType, typename Base>
KeyType AbstractStrategy<KeyType, Base>::activeModuleName() const {
    return m_activeModuleName;
}

template<typename KeyType, typename Base>
Base *AbstractStrategy<KeyType, Base>::activeModule() const {
    return m_activeModule;
}

}

#endif // KMODULESWITCH_H
