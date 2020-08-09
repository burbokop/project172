#ifndef SPRITEASSETEXECUTOR_H
#define SPRITEASSETEXECUTOR_H

#include "assetexecutor.h"



class SpriteAssetExecutor : public AssetExecutor {
public:
    SpriteAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *) override;
};

#endif // SPRITEASSETEXECUTOR_H
