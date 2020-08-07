#ifndef LOADABLE_H
#define LOADABLE_H


#include "json/json.h"
#include "animator.h"
#include "time/timer.h"
#include "audio/audioplayer.h"

#include <engine/variant.h>


class Loadable {
    friend class AssetManager;
    std::map<std::string, e172::Variant> m_assets;
    std::string m_className;
    std::string m_loadableId;
protected:
    virtual void initialized() {};
public:
    Loadable();


    template<typename T>
    T asset(const std::string &name, const T &defaultValue = T(), bool *ok = nullptr) const {
        const auto it = m_assets.find(name);
        if(it != m_assets.end() && it->second.containsType<T>()) {
            if(ok)
                *ok = true;
            return it->second.value<T>();
        }
        if(ok)
            *ok = false;
        return defaultValue;
    }

    virtual ~Loadable();
    std::string className() const;
    std::string loadableId() const;
};

#endif // LOADABLE_H
