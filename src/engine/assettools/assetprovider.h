#ifndef ASSETPROVIDER_H
#define ASSETPROVIDER_H

#include <src/engine/memcontrol/abstractfactory.h>
#include <memory>
#include "loadable.h"


namespace e172 {

class AbstractAssetExecutor;
class AbstractGraphicsProvider;
class AbstractAudioProvider;
class Context;

class AssetProvider {
    friend class GameApplication;
    AbstractGraphicsProvider *m_graphicsProvider = nullptr;
    AbstractAudioProvider *m_audioProvider = nullptr;
    Context *m_context = nullptr;

    struct LoadableTemplate {
        std::string className;
        std::map<std::string, e172::Variant> assets;
    };
    AbstractFactory<std::string, Loadable> m_factory;
    std::map<std::string, LoadableTemplate> templates;
    std::map<std::string, std::shared_ptr<AbstractAssetExecutor>> executors;

    void processFile(std::string file, std::string path);
public:
    Loadable *createLoadable(std::string templateId);
    template<typename T>
    T *createLoadable(std::string templateId) {
        const auto o = createLoadable(templateId);
        const auto l = dynamic_cast<T*>(o);
        if(l)
            return l;

        delete o;
        return nullptr;
    }
    AssetProvider();
    void searchInFolder(std::string path);
    std::vector<std::string> loadableNames();

    template<typename T>
    void registerType() {
        m_factory.registerType<T>();
    }

    void installExecutor(const std::string &id, const std::shared_ptr<AbstractAssetExecutor> &executor);
};

}

#endif // ASSETPROVIDER_H
