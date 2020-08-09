#ifndef NUMBERASSETEXECUTOR_H
#define NUMBERASSETEXECUTOR_H

#include "assetexecutor.h"



class NumberAssetExecutor : public AssetExecutor {
public:
    NumberAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *, e172::AbstractAudioProvider *) override;
};

#endif // NUMBERASSETEXECUTOR_H
