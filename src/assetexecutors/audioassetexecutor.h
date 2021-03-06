#ifndef AUDIOASSETEXECUTOR_H
#define AUDIOASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>



class AudioAssetExecutor : public e172::AbstractAssetExecutor {
public:
    AudioAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const e172::Variant &value, e172::AbstractGraphicsProvider*, e172::AbstractAudioProvider *audioProvider) override;
};

#endif // AUDIOASSETEXECUTOR_H
