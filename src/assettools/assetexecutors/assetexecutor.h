#ifndef ASSETEXECUTOR_H
#define ASSETEXECUTOR_H

#include <engine/variant.h>

#include <json/json.h>

#include <audio/abstractaudioprovider.h>

namespace e172 {
class AbstractGraphicsProvider;
}

class AssetExecutor {
    friend class AssetProvider;
    std::string executor_path;
public:
    std::string fullPath(const std::string &path);
    AssetExecutor();
    virtual ~AssetExecutor();
    virtual e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *audioProvider) = 0;
};

#endif // ASSETEXECUTOR_H
