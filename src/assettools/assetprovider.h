    #ifndef ASSETPROVIDER_H
#define ASSETPROVIDER_H

#include <iostream>
#include <json/json.h>
#include <SDL2/SDL_image.h>
#include <assettools/assetexecutors/assetexecutor.h>
#include <engine/abstractfactory.h>


#include "loadable.h"
#include <src/memcontrol/kabstractfactory.h>



class AssetProvider : public Object {
    struct LoadableTemplate {
        std::string className;
        std::map<std::string, e172::Variant> assets;
    };
    e172::AbstractFactory<std::string, Loadable> m_factory;
    std::map<std::string, LoadableTemplate> templates;
    std::map<std::string, std::shared_ptr<AssetExecutor>> executors;

    void processFile(std::string file, std::string path, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *audioProvider);
public:
    Loadable *createLoadable(std::string key);
    AssetProvider();
    void searchInFolder(std::string path, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *audioProvider);
    std::vector<std::string> loadableNames();

    template<typename T>
    void registerType() {
        m_factory.registerType<T>();
    }

    void installExecutor(const std::string &id, const std::shared_ptr<AssetExecutor> &executor);
};

#endif // ASSETPROVIDER_H
