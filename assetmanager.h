#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <iostream>
#include <jsoncpp/json/json.h>
#include <SDL2/SDL_image.h>

#include "filesystem.h"
#include "loadable.h"
#include "units/movable.h"
#include "capabilities/modules/weapon.h"

class AssetManager : public Object
{   
private:
    bool loadAudio;

    std::map<std::string, Loadable*> assets;

    std::string getSufix(std::string string);
    std::string addPrefix(std::string string, std::string prefix);

    void processFile(std::string file, std::string location);
public:
    AssetManager();
    void search(std::string path);
    Loadable *getAsset(std::string key);
    Loadable *copyAsset(std::string key);
};

#endif // ASSETMANAGER_H
