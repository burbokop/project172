    #ifndef ASSETPROVIDER_H
#define ASSETPROVIDER_H

#include <iostream>
#include <object.h>
#include <json/json.h>
#include <SDL2/SDL_image.h>
#include <engine/abstractfactory.h>


#include "loadable.h"
#include <src/memcontrol/kabstractfactory.h>


namespace e172 {

class AbstractAssetExecutor;
class AbstractGraphicsProvider;
class AbstractAudioProvider;

class AssetProvider : public Object {
    struct LoadableTemplate {
        std::string className;
        std::map<std::string, e172::Variant> assets;
    };
    e172::AbstractFactory<std::string, Loadable> m_factory;
    std::map<std::string, LoadableTemplate> templates;
    std::map<std::string, std::shared_ptr<AbstractAssetExecutor>> executors;

    void processFile(std::string file, std::string path, AbstractGraphicsProvider *graphicsProvider, AbstractAudioProvider *audioProvider);
public:
    Loadable *createLoadable(std::string key);
    AssetProvider();
    void searchInFolder(std::string path, AbstractGraphicsProvider *graphicsProvider, AbstractAudioProvider *audioProvider);
    std::vector<std::string> loadableNames();

    template<typename T>
    void registerType() {
        m_factory.registerType<T>();
    }

    void installExecutor(const std::string &id, const std::shared_ptr<AbstractAssetExecutor> &executor);
};

}

#endif // ASSETPROVIDER_H
