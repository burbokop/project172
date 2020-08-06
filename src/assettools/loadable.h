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
protected:


    Json::Value root;
    Animator animator;
    AudioPlayer audioPlayer;
    Timer timer = Timer(100);
    e172::Vector attachOffset;

public:
    Loadable();
    Loadable(Loadable *tmp);
    Loadable(Json::Value root, Animator animator = Animator(), AudioPlayer audioPlayer = AudioPlayer(), Timer timer = Timer(100), e172::Vector offset = e172::Vector());
    Loadable(const Loadable &object);

    std::string getAssetClass();

    void clone(Loadable *dst);

    template<typename T>
    T asset(const std::string &name) const {
        const auto it = m_assets.find(name);
        if(it != m_assets.end() && it->second.containsType<T>()) {
            return it->second.value<T>();
        }
        return T();
    }

    virtual ~Loadable();
};

#endif // LOADABLE_H
