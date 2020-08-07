#ifndef AUDIOASSETEXECUTOR_H
#define AUDIOASSETEXECUTOR_H

#include "assetexecutor.h"

class AudioAssetExecutor : public AssetExecutor {
public:
    AudioAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider*) override;
};

#endif // AUDIOASSETEXECUTOR_H
