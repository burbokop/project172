#ifndef NUMBERASSETEXECUTOR_H
#define NUMBERASSETEXECUTOR_H

#include <src/engine/assettools/abstractassetexecutor.h>



class NumberAssetExecutor : public e172::AbstractAssetExecutor {
public:
    NumberAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *, e172::AbstractAudioProvider *) override;
};

#endif // NUMBERASSETEXECUTOR_H
