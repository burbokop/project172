#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <iostream>
#include <json/json.h>
#include <SDL2/SDL_image.h>


#include "loadable.h"


class AssetManager : public Object {
    class AssetTemplate {
        std::list<e172::Variant> properties;
    };

private:
    bool loadAudio;

    std::map<std::string, Loadable*> assets;
    std::map<std::string, AssetTemplate> templates;


    void processFile(std::string file, std::string location, e172::AbstractGraphicsProvider *graphicsProvider);
    void processFileAlternative(std::string file, std::string location, e172::AbstractGraphicsProvider *graphicsProvider);
    Loadable *getAsset(std::string key);
public:
    AssetManager();
    void search(std::string path, e172::AbstractGraphicsProvider *renderEngine);
    Loadable *copyAsset(std::string key);
    std::vector<std::string> getKeys();
};

#endif // ASSETMANAGER_H
