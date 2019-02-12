#include "assetmanager.h"


AssetManager::AssetManager() {

}


std::string AssetManager::getSufix(std::string string) {
    return string.substr(string.find_last_of('.'), string.length() - 1);
}

std::string AssetManager::addPrefix(std::string string, std::string prefix) {
    if(string[0] == '.') string.erase(0, 1);
    if(string[0] != '/') string = '/' + string;
    if(prefix[prefix.length() - 1] == '/') prefix.pop_back();

    return prefix + string;
}

void AssetManager::search(std::string path) {
    if(path[path.length() - 1] == '/') path.pop_back();
    std::vector<std::string> items = FileSystem::readDir(path);
    for(unsigned long long i = 0, L = items.size(); i < L; i++) {
        std::string item = items[i];
        std::string file = path + '/' + item;
        if(FileSystem::isDir(file)) {
            search(file);
        } else {
            processFile(file, path);
        }
    }
}

Loadable *AssetManager::getAsset(std::string key) {
    if(assets.find(key) == assets.end()) {
        std::cerr << "AssetManager (error):\n key: " << key << " not found\n";
        return new Loadable();
    } else {
        return assets[key];
    }
}

Loadable *AssetManager::copyAsset(std::string key) {
    Loadable *tmp = getAsset(key);
    std::string assetClass = tmp->getAssetClass();

    if(assetClass == "player") return new Player(tmp);

    if(assetClass == "movable") return new Movable(tmp);
    if(assetClass == "ship") return new Ship(tmp);
    if(assetClass == "projectile") return new Projectile(tmp);

    if(assetClass == "station") return new Station(tmp);

    if(assetClass == "module") return new Module(tmp);
    if(assetClass == "weapon") return new Weapon(tmp);
    if(assetClass == "engine") return new Engine(tmp);
    if(assetClass == "warp-drive") return new WarpDrive(tmp);

    std::cout << "AssetManager (error):\n undefined asset class ( key: " << key << " )\n";
    return nullptr;
}

std::vector<std::string> AssetManager::getKeys() {
    std::vector<std::string> result;
    for (std::map<std::string, Loadable*>::iterator it = assets.begin(); it != assets.end(); it++) {
        result.push_back(it->first);
    }
    return result;
}

void AssetManager::processFile(std::string file, std::string location) {
    std::string sufix = getSufix(file);

    if(sufix == ".json") {
        //std::cout << "AssetManager:\n file: " << file << "\n type: json\n";
        std::string content = FileSystem::readFile(file);
        Json::Reader reader;
        Json::Value root;
        reader.parse(content, root);
        Json::Value key = root["key"];
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
                     anim = Animator(IMG_Load(addPrefix(spritesheet.asString(), location).c_str()), frames.isNull() ? 1 : frames.asInt(), tracks.isNull() ? 1 : tracks.asInt());
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
                anim = Animator(IMG_Load(addPrefix(sprite.asString(), location).c_str()));
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
                            Mix_LoadWAV(addPrefix(audioStart.asString(), location).c_str()),
                            Mix_LoadWAV(addPrefix(audioLoop.asString(), location).c_str()),
                            Mix_LoadWAV(addPrefix(audioStop.asString(), location).c_str())
                        );
                    } else {
                        audioPlayer = AudioPlayer(
                            Mix_LoadWAV(addPrefix(audioStart.asString(), location).c_str())
                        );
                    }
                }
            } else if (audio.isString()) {
                audioPlayer = AudioPlayer(
                    Mix_LoadWAV(addPrefix(audio.asString(), location).c_str())
                );
            }

            long intervalValue = 1000;

            Json::Value rate = root["rate"];
            Json::Value interval = root["interval"];

            if(rate.isNumeric()) {
                intervalValue = static_cast<long>(60000 / rate.asDouble());
            } else if (interval.isNumeric()) {
                intervalValue = static_cast<long>(interval.asDouble());
            }
            Timer timer(intervalValue);

            double offsetX = 0, offsetY = 0;
            if(!offset.isNull()) {
                offsetX = offset.get("x", 0.0).asDouble();
                offsetY = offset.get("y", 0.0).asDouble();
            }
            Vector offsetVector(offsetX, offsetY);

            assets[key.asString()] = new Loadable(root, anim, audioPlayer, timer, offsetVector);
        }
    }
};
