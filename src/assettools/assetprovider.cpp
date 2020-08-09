#include "assetprovider.h"


#include "filesystem.h"
#include "debug.h"
#include "capabilities/player.h"
#include "capabilities/modules/weapon.h"
#include "capabilities/modules/engine.h"
#include "capabilities/modules/thruster.h"
#include "units/projectile.h"
#include "units/station.h"



#include <engine/graphics/abstractgraphicsprovider.h>


AssetProvider::AssetProvider() {}


void AssetProvider::searchInFolder(std::string path, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *audioProvider) {
    Debug::out("AssetProvider: assets path: " + path);

    if(path[path.length() - 1] == '/') path.pop_back();
    std::vector<std::string> items = FileSystem::readDir(path);
    for(unsigned long long i = 0, L = items.size(); i < L; i++) {
        std::string item = items[i];
        std::string file = path + '/' + item;
        if(FileSystem::isDir(file)) {
            searchInFolder(file, graphicsProvider, audioProvider);
        } else {
            processFile(file, path, graphicsProvider, audioProvider);
        }
    }
}

Loadable *AssetProvider::createLoadable(std::string key) {
    const auto it = templates.find(key);
    if(it == templates.end()) {
        Debug::err(Debug::Code::ASSET_ID_NOT_FOUND, __PRETTY_FUNCTION__, key);
        return nullptr;
    }

    auto result = m_factory.create(it->second.className);
    if(!result) {
        Debug::err(Debug::Code::ASSET_TYPE_NOT_REGISTERED, __PRETTY_FUNCTION__, "class name: " + it->second.className + ", id: " + it->first);
        return nullptr;
    }

    result->m_assets = it->second.assets;
    result->m_className = it->second.className;
    result->m_loadableId = it->first;
    result->m_assetProvider = this;

    for(auto f : result->initialize_functions) {
        f();
    }
    result->initialize_functions.clear();
    result->released = true;
    return result;
}

std::vector<std::string> AssetProvider::loadableNames() {
    std::vector<std::string> result;
    for (auto it = templates.begin(); it != templates.end(); it++) {
        result.push_back(it->first);
    }
    return result;
}

void AssetProvider::installExecutor(const std::string &id, const std::shared_ptr<AssetExecutor> &executor) {
    executors[id] = executor;
}

//void AssetProvider::processFile(std::string file, std::string location, e172::AbstractGraphicsProvider *graphicsProvider) {
//    std::string sufix = FileSystem::getSufix(file);
//    if(sufix == ".json") {
//        std::string content = FileSystem::readFile(file);
//        Json::Reader reader;
//        Json::Value root;
//        reader.parse(content, root);
//        Json::Value key = root["id"];
//        if(!key.isNull()) {
//
//            unsigned intervalValue = 1000;
//
//            Json::Value rate = root["rate"];
//            Json::Value interval = root["interval"];
//
//            if(rate.isNumeric()) {
//                intervalValue = static_cast<unsigned>(60000 / rate.asDouble());
//            } else if (interval.isNumeric()) {
//                intervalValue = static_cast<unsigned>(interval.asDouble());
//            }
//            Timer timer(intervalValue);
//
//
//            //assets[key.asString()] = new Loadable(root, anim, audioPlayer, timer, offsetVector);
//        }
//    }
//}

void AssetProvider::processFile(std::string file, std::string path, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *audioProvider) {
    std::string sufix = FileSystem::getSufix(file);
    if(sufix == ".json") {
        const std::string content = FileSystem::readFile(file);
        Json::Reader reader;
        Json::Value root;
        reader.parse(content, root);
        const auto id = root["id"];
        const auto className = root["class"];
        if(id.isNull() || className.isNull()) {
            if(id.isNull()) {
                Debug::err(Debug::Code::ASSET_NOT_CONTAINS_ID, __PRETTY_FUNCTION__, path);
            } else {
                Debug::err(Debug::Code::ASSET_NOT_CONTAINS_CLASS_NAME, __PRETTY_FUNCTION__, path);
            }
            return;
        }

        LoadableTemplate newTemplate;
        newTemplate.className = className.asString();
        for(auto item = root.begin(); item != root.end(); ++item) {
            const std::string assetId = item.key().asString();
            if(assetId != "class" && assetId != "id") {
                auto it = executors.find(assetId);
                if(it != executors.end() && it->second){
                    if(item->isNull()) {
                        Debug::err(Debug::Code::ASSET_IS_NULL, __PRETTY_FUNCTION__, "asset id: " + assetId + " path: " + path);
                    } else {
                        it->second->executor_path = path;
                        newTemplate.assets[assetId] = it->second->proceed(*item, graphicsProvider, audioProvider);
                    }
                } else {
                    Debug::err(Debug::Code::EXECUTOR_NOT_INSTALLED_FOR_ASSET, __PRETTY_FUNCTION__, "asset id: " + assetId + " path: " + path);
                }
            }
        }
        templates[id.asString()] = newTemplate;
    }
};
