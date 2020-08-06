#include "assetmanager.h"


#include "filesystem.h"
#include "debug.h"
#include "capabilities/player.h"
#include "capabilities/modules/weapon.h"
#include "capabilities/modules/engine.h"
#include "capabilities/modules/thruster.h"
#include "units/projectile.h"
#include "units/station.h"



#include <engine/graphics/abstractgraphicsprovider.h>


AssetManager::AssetManager() {}


void AssetManager::searchInFolder(std::string path, e172::AbstractGraphicsProvider *renderEngine) {
    Debug::out("AssetManager: assets path: " + path);

    if(path[path.length() - 1] == '/') path.pop_back();
    std::vector<std::string> items = FileSystem::readDir(path);
    for(unsigned long long i = 0, L = items.size(); i < L; i++) {
        std::string item = items[i];
        std::string file = path + '/' + item;
        if(FileSystem::isDir(file)) {
            searchInFolder(file, renderEngine);
        } else {
            //processFile(file, path, renderEngine);
            processFileAlternative(file, path, renderEngine);
        }
    }
}

Loadable *AssetManager::createLoadable(std::string key) {
    const auto it = templates.find(key);
    if(it == templates.end()) {
        Debug::err(Debug::Code::ASSET_ID_NOT_FOUND, __PRETTY_FUNCTION__, key);
        return nullptr;
    }

    auto result = m_factory.create(it->second.className);
    if(!result) {
        Debug::err(Debug::Code::ASSET_TYPE_NOT_REGISTERED, __PRETTY_FUNCTION__, key);
        return nullptr;
    }

    result->m_assets = it->second.assets;
    return result;
}

std::vector<std::string> AssetManager::loadableNames() {
    std::vector<std::string> result;
    for (auto it = templates.begin(); it != templates.end(); it++) {
        result.push_back(it->first);
    }
    return result;
}

void AssetManager::processFile(std::string file, std::string location, e172::AbstractGraphicsProvider *graphicsProvider) {
    std::string sufix = FileSystem::getSufix(file);
    if(sufix == ".json") {
        std::string content = FileSystem::readFile(file);
        Json::Reader reader;
        Json::Value root;
        reader.parse(content, root);
        Json::Value key = root["id"];
        if(!key.isNull()) {
            Animator anim;
            Json::Value animation = root["animation"];
            Json::Value sprite = root["sprite"];
            Json::Value offset = root["offset"];

            if(!animation.isNull()) {
                 Json::Value spritesheet = animation["spritesheet"];
                 Json::Value frames = animation["frames"];
                 Json::Value tracks = animation["tracks"];
                 Json::Value play = animation["play"];
                 if(!spritesheet.isNull()) {
                     anim = Animator(graphicsProvider->loadImage(FileSystem::addPrefix(spritesheet.asString(), location)), frames.isNull() ? 1 : frames.asInt(), tracks.isNull() ? 1 : tracks.asInt());
                     if(play.isString()) {
                         if(play == "loop") {
                             anim.play(Animator::LOOP);
                         } else {
                             anim.play(Animator::NOTRENDER);
                         }
                     } else {
                        anim.play(Animator::LOOP);
                     }
                 }
            } else if (!sprite.isNull()) {
                anim = Animator(graphicsProvider->loadImage(FileSystem::addPrefix(sprite.asString(), location)));
                anim.play(Animator::LOOP);
            }

            AudioPlayer audioPlayer;
            Json::Value audio = root["audio"];
            if(audio.isObject()) {
                Json::Value audioStart = audio["start"];
                Json::Value audioLoop = audio["loop"];
                Json::Value audioStop = audio["stop"];

                if(audioStart.isString()) {
                    if(audioLoop.isString() && audioStop.isString()) {
                        Debug::log("audio exists: " + audioStart.asString() + " : " + key.asString());
                        audioPlayer = AudioPlayer(
                            Mix_LoadWAV(FileSystem::addPrefix(audioStart.asString(), location).c_str()),
                            Mix_LoadWAV(FileSystem::addPrefix(audioLoop.asString(), location).c_str()),
                            Mix_LoadWAV(FileSystem::addPrefix(audioStop.asString(), location).c_str())
                        );
                    } else {
                        audioPlayer = AudioPlayer(
                            Mix_LoadWAV(FileSystem::addPrefix(audioStart.asString(), location).c_str())
                        );
                    }
                }
            } else if (audio.isString()) {
                audioPlayer = AudioPlayer(
                    Mix_LoadWAV(FileSystem::addPrefix(audio.asString(), location).c_str())
                );
            }

            unsigned intervalValue = 1000;

            Json::Value rate = root["rate"];
            Json::Value interval = root["interval"];

            if(rate.isNumeric()) {
                intervalValue = static_cast<unsigned>(60000 / rate.asDouble());
            } else if (interval.isNumeric()) {
                intervalValue = static_cast<unsigned>(interval.asDouble());
            }
            Timer timer(intervalValue);

            double offsetX = 0, offsetY = 0;
            if(!offset.isNull()) {
                offsetX = offset.get("x", 0.0).asDouble();
                offsetY = offset.get("y", 0.0).asDouble();
            }
            e172::Vector offsetVector(offsetX, offsetY);

            //assets[key.asString()] = new Loadable(root, anim, audioPlayer, timer, offsetVector);
        }
    }
}

void AssetManager::processFileAlternative(std::string file, std::string location, e172::AbstractGraphicsProvider *graphicsProvider) {
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
                Debug::err(Debug::Code::ASSET_NOT_CONTAINS_ID, __PRETTY_FUNCTION__, location);
            } else {
                Debug::err(Debug::Code::ASSET_NOT_CONTAINS_CLASS_NAME, __PRETTY_FUNCTION__, location);
            }
            return;
        }

        for(auto item = root.begin(); item != root.end(); item++) {
            std::string key = item.key().asString();

            auto it = executors.find(key);

            std::cout << "Json parse "<< key << " " << id << " " << className << " " << *item << std::endl;

            if(it != executors.end()){

                it->second->proceed(*item);
            }

            //std::cout << "\t" <<  << "\n";
        }
        std::cout << "end proceed asset: " << id << "\n\n";
    }
};
