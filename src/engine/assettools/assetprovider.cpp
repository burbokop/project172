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
        const auto root = Variant::fromJson(Additional::readFile(file)).toMap();
        if(root.size() == 0) {
            Debug::warning("Empty json object detected or parsing error. file:", file);
            return;
        }

        const auto id = Additional::value(root, "id");
        const auto className = Additional::value(root, "class");
        if(id.isNull() || className.isNull()) {
            if(id.isNull()) {
                Debug::warning("Template id missing. file:", file);
            } else {
                Debug::warning("Template class name missing. file:", file);
            }
            return;
        }

        LoadableTemplate newTemplate;
        newTemplate.className = className.toString();
        for(auto item = root.begin(); item != root.end(); ++item) {
            const auto& assetId = item->first;
            if(assetId != "class" && assetId != "id") {
                if(item->second.isNull()) {
                    Debug::warning("Asset is null. Id:", assetId, "file:", file);
                } else {
                    auto it = executors.find(assetId);
                    if(it != executors.end() && it->second) {
                        it->second->executor_path = m_context->absolutePath(path);
                        newTemplate.assets[assetId] = it->second->proceed(item->second, m_graphicsProvider, m_audioProvider);
                    } else {
                        newTemplate.assets[assetId] = item->second;
                    }
                }
            }
        }
        templates[id.toString()] = newTemplate;
    }
};

}
