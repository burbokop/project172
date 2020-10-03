#ifndef ABSTRACTASSETEXECUTOR_H
#define ABSTRACTASSETEXECUTOR_H

#include <src/engine/variant.h>

namespace e172 {
class AbstractGraphicsProvider;
class AbstractAudioProvider;

class AbstractAssetExecutor {
    friend class AssetProvider;
    std::string executor_path;
public:
    std::string fullPath(const std::string &path);
    AbstractAssetExecutor();
    virtual ~AbstractAssetExecutor();
    virtual Variant proceed(const Variant &value, AbstractGraphicsProvider *graphicsProvider, AbstractAudioProvider *audioProvider) = 0;
};


}

#endif // ABSTRACTASSETEXECUTOR_H
