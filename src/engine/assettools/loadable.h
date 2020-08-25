#ifndef LOADABLE_H
#define LOADABLE_H


#include <src/engine/variant.h>

namespace e172 {


class AssetProvider;
class Loadable {
    friend AssetProvider;
    std::map<std::string, e172::Variant> m_assets;
    std::string m_className;
    std::string m_loadableId;
    AssetProvider *m_assetProvider = nullptr;

    std::vector<std::function<void(void)>> initialize_functions;
    bool released = false;
protected:
    void registerInitFunction(const std::function<void(void)> &function);
    template<typename C>
    void registerInitFunction(C *obj, void(C::*f)()) { registerInitFunction(obj->*f); }
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
    AssetProvider *assetProvider() const;
};

}

#endif // LOADABLE_H
