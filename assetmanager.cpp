#include "assetmanager.h"


AssetManager::AssetManager()
{

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
    for(unsigned long i = 0, L = items.size(); i < L; i++) {
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

    //deprecated
    if(assetClass == "ship") assetClass = "movable";
    //----------

    if(assetClass == "movable") return new Movable(tmp);
    //if(assetClass == "ship") return new Movable(tmp);
    if(assetClass == "projectile") return new Projectile(tmp);

    if(assetClass == "module") return new Module(tmp);
    if(assetClass == "weapon") return new Weapon(tmp);
    if(assetClass == "engine") return new Engine(tmp);
    if(assetClass == "warp-drive") return new WarpDrive(tmp);


    //if(assetClass == "movable") return new Movable(tmp);
    //if(assetClass == "movable") return new Movable(tmp);

    std::cout << "AssetManager (error):\n undefined asset class\n";
    return nullptr;
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

            assets[key.asString()] = new Loadable(root, anim, AudioPlayer(), timer, offsetVector);
        }
    }


        /*
        if(!root["animation"].isNull()) {
        }



        /*
        } else resource.hasSprite = false;

        if(resource.animation && resource.animation.spritesheet) {
            resource.animation = new api.Anim(api.oh.loadSurface(
                addPrefix(resource.animation.spritesheet, path)),
                resource.animation.w,
                resource.animation.h,
                resource.animation.mode,
                resource.animation.interval
            );
        }

        if(resource.offset && resource.offset.coords) {
            resource.offset = new api.oh.math.Vector(resource.offset.coords[0], resource.offset.coords[1]);
        }

        if(resource.audio && !noAudio) {
            for(const sample in resource.audio) {
                resource.audio[sample] = api.oh.sound.load(addPrefix(resource.audio[sample], path));
            }
        }

        if(resource.key) {
            resources[resource.key] = resource;
        }
    }

        /*
    } else if ((sufix == ".mp3" || sufix == ".ogg" || sufix == ".wav") && loadAudio) {
        std::cout << "file: " << file << "  type: sound\n";
        /*
        let name = file.split('/');
        name = name[name.length - 1];
        name = name.split('.')[0];
        sounds[name] = api.oh.sound.load(file);
    }
        */

};


/*

const processFile = (file, path, noAudio) => {
    const sufix = getSufix(file);
    if(sufix === 'json') {
        const resource = JSON.parse(api.fs.readFileSync(file, { encoding: 'utf8' }), functionParser);
        if(resource.sprite) {
            resource.sprite = api.oh.loadSurface(addPrefix(resource.sprite, path));
            resource.hasSprite = true;
        } else resource.hasSprite = false;

        if(resource.animation && resource.animation.spritesheet) {
            resource.animation = new api.Anim(api.oh.loadSurface(
                addPrefix(resource.animation.spritesheet, path)),
                resource.animation.w,
                resource.animation.h,
                resource.animation.mode,
                resource.animation.interval
            );
        }

        if(resource.offset && resource.offset.coords) {
            resource.offset = new api.oh.math.Vector(resource.offset.coords[0], resource.offset.coords[1]);
        }

        if(resource.audio && !noAudio) {
            for(const sample in resource.audio) {
                resource.audio[sample] = api.oh.sound.load(addPrefix(resource.audio[sample], path));
            }
        }

        if(resource.key) {
            resources[resource.key] = resource;
        }
    } else if ((sufix === 'mp3' || sufix === 'ogg' || sufix === 'wav') && !noAudio) {
        let name = file.split('/');
        name = name[name.length - 1];
        name = name.split('.')[0];
        sounds[name] = api.oh.sound.load(file);
    }
};

//oh.sound.play(, 1);


const loadDir = (path, noAudio) => {

}

*/
