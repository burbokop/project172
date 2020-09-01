#include "assetprovider.h"

#include <src/engine/debug.h>
#include <src/engine/graphics/abstractgraphicsprovider.h>
#include <src/engine/additional.h>
#include "abstractassetexecutor.h"

namespace e172 {


AssetProvider::AssetProvider() {}


void AssetProvider::searchInFolder(std::string path) {

    if(path[path.length() - 1] == '/') path.pop_back();
    std::vector<std::string> items = Additional::directoryContent(path);
    for(unsigned long long i = 0, L = items.size(); i < L; i++) {
        std::string item = items[i];
        std::string file = path + '/' + item;
        if(Additional::isDirectory(file)) {
            searchInFolder(file);
        } else {
            processFile(file, path);
        }
    }
}

Loadable *AssetProvider::createLoadable(std::string templateId) {
    const auto it = templates.find(templateId);
    if(it == templates.end()) {
        Debug::warning("AssetProvider::createLoadable: Loadable template not found for id:", templateId);
        return nullptr;
    }

    auto result = m_factory.create(it->second.className);
    if(!result) {
        Debug::warning("AssetProvider::createLoadable: Type not registered:", it->second.className, "( template id: ", templateId, ")");
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

void AssetProvider::installExecutor(const std::string &id, const std::shared_ptr<AbstractAssetExecutor> &executor) {
    executors[id] = executor;
}

void AssetProvider::processFile(std::string file, std::string path) {
    std::string sufix = Additional::fileSufix(file);
    if(sufix == ".json") {
        const std::string content = Additional::readFile(file);
        Json::Reader reader;
        Json::Value root;
        reader.parse(content, root);
        const auto id = root["id"];
        const auto className = root["class"];
        if(id.isNull() || className.isNull()) {
            if(id.isNull()) {
                Debug::warning("Template id missing. path:", path);
            } else {
                Debug::warning("Template class name missing. path:", path);
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
                        Debug::warning("Asset is null. Id:", assetId, "path: ", path);
                    } else {
                        it->second->executor_path = m_context->absolutePath(path);
                        newTemplate.assets[assetId] = it->second->proceed(*item, m_graphicsProvider, m_audioProvider);
                    }
                } else {
                    Debug::warning("Executor not installed for asset:", assetId, "path: ", path);
                }
            }
        }
        templates[id.asString()] = newTemplate;
    }
};

}
