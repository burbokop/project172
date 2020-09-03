#ifndef SPRITEASSETEXECUTOR_H
#define SPRITEASSETEXECUTOR_H

#include <src/engine/assettools/abstractassetexecutor.h>



class SpriteAssetExecutor : public e172::AbstractAssetExecutor {
public:
    SpriteAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *) override;
};

#endif // SPRITEASSETEXECUTOR_H