#ifndef ANIMATORASSETEXECUTOR_H
#define ANIMATORASSETEXECUTOR_H

#include "assetexecutor.h"


class AnimatorAssetExecutor : public AssetExecutor {
public:
    AnimatorAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *) override;
};

#endif // ANIMATORASSETEXECUTOR_H
