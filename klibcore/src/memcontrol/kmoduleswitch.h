#ifndef KMODULESWITCH_H
#define KMODULESWITCH_H

#include "kabstractfactory.h"

#include <src/kmacro.h>
#include <list>

template<typename KeyType, typename Base>
class KModuleSwitch {
    KAbstractFactory<KeyType, Base> factory;
    std::list<KeyType> m_moduleNames;
    KeyType m_activeModuleName;
    Base *m_activeModule = nullptr;

public:
    KModuleSwitch() {}

    bool activateModule(const KeyType &moduleName);
    bool deactivateModule();

    template<typename T>
    void registerModule(KeyType moduleName = KeyType()) {
        const auto n = moduleName.isEmpty() ? factory.template registerType<T>() : factory.template registerType<T>(moduleName);
        if(!m_moduleNames.contains(n)) {
            m_moduleNames.push_back(n);
        }
    }
    std::list<KeyType> moduleNames() const;
    KeyType activeModuleName() const;
    Base *activeModule() const;
};

template<typename KeyType, typename Base>
bool KModuleSwitch<KeyType, Base>::activateModule(const KeyType &moduleName) {
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
bool KModuleSwitch<KeyType, Base>::deactivateModule() {
    if(m_activeModule) {
        delete m_activeModule;
        m_activeModule = nullptr;
        m_activeModuleName = KeyType();
        return true;
    }
    return false;
}

template<typename KeyType, typename Base>
std::list<KeyType> KModuleSwitch<KeyType, Base>::moduleNames() const {
    return m_moduleNames;
}

template<typename KeyType, typename Base>
KeyType KModuleSwitch<KeyType, Base>::activeModuleName() const {
    return m_activeModuleName;
}

template<typename KeyType, typename Base>
Base *KModuleSwitch<KeyType, Base>::activeModule() const {
    return m_activeModule;
}


#endif // KMODULESWITCH_H
