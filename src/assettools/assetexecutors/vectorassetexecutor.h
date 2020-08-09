#ifndef VECTORASSETEXECUTOR_H
#define VECTORASSETEXECUTOR_H

#include "assetexecutor.h"



class VectorAssetExecutor : public AssetExecutor {
public:
    VectorAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *, e172::AbstractAudioProvider *) override;
};

#endif // VECTORASSETEXECUTOR_H
