#ifndef MAPASSETEXECUTOR_H
#define MAPASSETEXECUTOR_H

#include <src/engine/assettools/abstractassetexecutor.h>




class MapAssetExecutor : public e172::AbstractAssetExecutor {
public:
    MapAssetExecutor();

    // AssetExecutor interface
public:
    virtual e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *, e172::AbstractAudioProvider *) override;
};

#endif // MAPASSETEXECUTOR_H
