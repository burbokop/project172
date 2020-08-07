#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <iostream>
#include <json/json.h>
#include <SDL2/SDL_image.h>
#include <assettools/assetexecutors/assetexecutor.h>


#include "loadable.h"
#include <src/memcontrol/kabstractfactory.h>


class AssetManager : public Object {
    struct LoadableTemplate {
        std::string className;
        std::map<std::string, e172::Variant> assets;
    };
    KAbstractFactory<std::string, Loadable> m_factory;
    std::map<std::string, LoadableTemplate> templates;
    std::map<std::string, std::shared_ptr<AssetExecutor>> executors;

    void processFileAlternative(std::string file, std::string path, e172::AbstractGraphicsProvider *graphicsProvider);
public:
    Loadable *createLoadable(std::string key);
    AssetManager();
    void searchInFolder(std::string path, e172::AbstractGraphicsProvider *renderEngine);
    std::vector<std::string> loadableNames();

    template<typename T>
    void registerType() {
        m_factory.registerType<T>();
    }

    void installExecutor(const std::string &id, const std::shared_ptr<AssetExecutor> &executor);
};

#endif // ASSETMANAGER_H
