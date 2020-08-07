#ifndef ASSETEXECUTOR_H
#define ASSETEXECUTOR_H

#include <engine/variant.h>

#include <json/json.h>

namespace e172 {
class AbstractGraphicsProvider;
}

class AssetExecutor {
    friend class AssetManager;
    std::string executor_path;
public:
    std::string fullPath(const std::string &path);
    AssetExecutor();
    virtual ~AssetExecutor();
    virtual e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider) = 0;
};

#endif // ASSETEXECUTOR_H
