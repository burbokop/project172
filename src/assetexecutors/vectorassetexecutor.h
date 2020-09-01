#ifndef VECTORASSETEXECUTOR_H
#define VECTORASSETEXECUTOR_H

#include <src/engine/assettools/abstractassetexecutor.h>




class VectorAssetExecutor : public e172::AbstractAssetExecutor {
public:
    VectorAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *, e172::AbstractAudioProvider *) override;
};

#endif // VECTORASSETEXECUTOR_H
