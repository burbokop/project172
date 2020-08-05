#ifndef KPULL_H
#define KPULL_H

#include "kabstractfactory.h"
#include <list>

/**
 * @brief The KPull class provides standart pull
 *
 * Template parameter <b>BaseClass</b> defines base type witch can be handled by pull.
 * Current instance of pull can only handle <b>BaseClass</b> type and inherited by.
 * Pull can not work with interfaces because them can not be created, but base type can be interface.
 *
 * @note KPull is available whithout Qt.
 */
template<typename KeyType, typename BaseClass>
class KPull {
    KAbstractFactory<KeyType, BaseClass> factory;
    std::list<BaseClass*> all;
    std::map<BaseClass*, bool> locked;
public:
    KPull() {}

    /**
     * @brief takeObject function issues free object from pull or creates new is no objects availble
     * @param className - type name of class needed to be taked
     * @return pointer to object taked from pull
     */
    BaseClass *takeObject(KeyType className) {
        for(auto a : all) {
            if(className == factory.type(a) && !locked[a]) {
                locked[a] = true;
                return a;
            }
        }

        auto obj = factory.create(className);
        all.push_back(obj);
        locked[obj] = true;
        return obj;
    }

    /**
     * @brief returnObject function retuns object back to pull
     * @param object
     * @return true if object belongs to this pull
     *
     * After calling this function you can not work with this object. You need perceive this operation as <b>delate</b>.
     * If you don't, this can cause undefined behaviour.
     */
    bool returnObject(BaseClass *object) {
        auto value = locked[object];
        if(value) {
            locked[object] = false;
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief clearAvailable function cleares instances witch is available for taking.
     */
    void clearAvailable() {
        auto it = all.begin();
        while (it != all.end()) {
            if(!locked[*it]) {
                delete *it;
                locked.erase(locked.find(*it));
                it = all.erase(it);
            } else {
                ++it;
            }
        }
    }

    /**
     * @brief termainteAll function cleares all instances
     */
    void termainteAll() {
        for(auto a : all) {
            delete a;
        }
        locked.clear();
        all.clear();
    }

    /**
     * @brief registerType function registers type <b>T</b>
     *
     * After calling this function type <b>T</b> becomes avalable for taking.
     */
    template<typename T>
    void registerType() {
        factory.template registerType<T>();
    }

    /**
     * @brief destructor cleares all avalable instances.
     */
    ~KPull() {
        clearAvailable();
    }
};

#endif // KPULL_H
